#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>

void display_usage(int opt)
{
    fprintf(stderr, "Unknown option -%c.\n", optopt);
    exit(EXIT_FAILURE);
}

void set_limits(time_value, mem_value)
{
    struct rlimit time_limit, mem_limit;

    time_limit.rlim_cur = time_value;
    time_limit.rlim_max = time_value;

    mem_limit.rlim_cur = mem_value;
    mem_limit.rlim_max = mem_value;

    setrlimit(RLIMIT_CPU, &time_limit);
    setrlimit(RLIMIT_AS, &mem_limit);
}

void run_command(char **command)
{
    int status;
    pid_t pid;
    long orig_eax;

    pid = fork();
    if (pid == 0)
    {

        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        if (execvp(*command, command) > 0)
        {
            fprintf(stderr, "Forking child failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        while (1)
        {
            wait(&status);
            if (WIFEXITED(status) || WIFSIGNALED(status))
                break;

            orig_eax = ptrace(PTRACE_PEEKUSER,
                              pid, 4 * ORIG_EAX,
                              NULL);

            printf("The child made a system call %ld\n", orig_eax);
            ptrace(PTRACE_CONT, pid, NULL, NULL);
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
            display_usage(opt);
            break;
        default:
            break;
        }
    }

    set_limits(atoi(time_value), atoi(mem_value));
    run_command(&argv[optind]);

    return EXIT_SUCCESS;
}
