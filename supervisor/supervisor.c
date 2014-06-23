#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/syscall.h>
#include "whitelist.h"

void print_error(int opt)
{
    fprintf(stderr, "Unknown option -%c.\n", optopt);
    exit(EXIT_FAILURE);
}

void set_limits(time_value, mem_value)
{
    struct rlimit time_limit, mem_limit;

    time_limit.rlim_cur = time_value;
    time_limit.rlim_max = time_value;
    setrlimit(RLIMIT_CPU, &time_limit);

    mem_limit.rlim_cur = mem_value;
    mem_limit.rlim_max = mem_value;
    setrlimit(RLIMIT_AS, &mem_limit);
}

char **parse_command(char *str)
{
    char **result = NULL;
    char *p = strtok(str, " ");
    int spaces = 0, i;

    // split string and append tokens to result

    while (p) {
        result = realloc (result, sizeof(char*) * ++spaces);

        if (result == NULL)
            exit(EXIT_FAILURE); // memory allocation failed

        result[spaces-1] = p;

        p = strtok (NULL, " ");
    }

    // realloc one extra element for the last NULL

    result = realloc(result, sizeof(char*) * (spaces+1));
    result[spaces] = 0;

    return result;
}

int run_command(char **command)
{
    int execcount = 0;
    int status;
    pid_t pid;
    long orig_eax;

    pid = fork();

    if (pid == 0)   // We are in the child process.
    {

        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        if (execvp(*command, command) > 0)
        {
            fprintf(stderr, "Forking child failed.\n");
            return EXIT_FAILURE;
        }
    }
    else            // We are in the parent process.
    {
        while (1)
        {
            wait(&status);

            /* If the child has exited cleanly or been
             * killed, break out of the loop and exit.
             */
            if (WIFEXITED(status) || WIFSIGNALED(status))
                break;

            // EAX register holds the number of the syscall.
            orig_eax = ptrace(PTRACE_PEEKUSER,
                              pid, 4 * ORIG_EAX,
                              NULL);

            /* SYS_execve call should be allowed twice
             * for the entry and exit of the initial
             * call that executes the given command
             */
            if (orig_eax == SYS_execve && execcount < 2)
            {
                execcount++;
            }
            else if (!whitelist[orig_eax])
            {
                printf("Illegal system call: %ld\n", orig_eax);
                kill(pid, SIGKILL);
                return EXIT_FAILURE;
            }

            /* Resume tracing and notify on next syscall. */
            ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
        }
    }

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    int opt = 0;
    int exit_code = 0;
    char *time_value = NULL;
    char *mem_value = NULL;
    char *command = NULL;
    char **split_command;

    opterr = 0;
    while ((opt = getopt(argc, argv, "t:m:c:")) != -1)
    {
        switch (opt)
        {
        case 't':
            time_value = optarg;
            break;
        case 'm':
            mem_value = optarg;
            break;
        case 'c':
            command = optarg;
            break;
        case '?':
            print_error(opt);
            break;
        default:
            break;
        }
    }

    set_limits(atoi(time_value), atoi(mem_value));
    split_command = parse_command(command);
    exit_code = run_command(split_command);
    free(split_command);

    return exit_code;
}
