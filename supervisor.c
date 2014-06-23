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

void run_command(char **command)
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
            exit(EXIT_FAILURE);
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
                exit(EXIT_FAILURE);
            }

            /* Resume tracing and notify on next syscall. */
            ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
        }
    }
}

int main(int argc, char **argv)
{
    int opt = 0;
    char *time_value = NULL;
    char *mem_value = NULL;
    char command[16][256];

    opterr = 0;
    while ((opt = getopt(argc, argv, "t:m:")) != -1)
    {
        switch (opt)
        {
        case 't':
            time_value = optarg;
            break;
        case 'm':
            mem_value = optarg;
            break;
        case '?':
            print_error(opt);
            break;
        default:
            break;
        }
    }

    set_limits(atoi(time_value), atoi(mem_value));
    run_command(&argv[optind]);

    return EXIT_SUCCESS;
}
