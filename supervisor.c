#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>

#define SHELL "/bin/sh"

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

void run_command(char *command)
{
    int status;
    pid_t child;
    long orig_eax;

    child = fork();
    if (child == 0)
    {

        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(SHELL, SHELL, "-c", command, NULL);
    }
    else
    {
        while (1)
        {
            wait(&status);

            if (WIFEXITED(status))
                break;

            orig_eax = ptrace(PTRACE_PEEKUSER,
                              child, 4 * ORIG_EAX,
                              NULL);

            printf("The child made a system call %ld\n", orig_eax);
            ptrace(PTRACE_CONT, child, NULL, NULL);
        }
    }
}

int main(int argc, char **argv)
{
    int opt = 0;
    char *time_value = NULL;
    char *mem_value = NULL;
    char command[256] = "\"";

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

    int i = 0;
    for (i=optind; i<argc; i++)
    {
        if (i > optind)
            strcat(command, " ");
        strcat(command, argv[i]);
    }
    strcat(command, "\"");

    printf("Time option: %s, Memory option: %s, Command: %s\n",
           time_value, mem_value, command);

    set_limits(atoi(time_value), atoi(mem_value));
    run_command(command);

    return EXIT_SUCCESS;
}
