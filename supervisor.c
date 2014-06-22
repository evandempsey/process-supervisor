#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void display_usage(int opt)
{
    fprintf(stderr, "Unknown option -%c.\n", optopt);
    exit(EXIT_FAILURE);
}


int main(int argc, char **argv)
{
    int opt = 0;
    char *time_value = NULL;
    char *mem_value = NULL;
    char command[256];

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
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    printf("Time option: %s, Memory option: %s, Command: %s\n",
        time_value, mem_value, command);

    return EXIT_SUCCESS;
}
