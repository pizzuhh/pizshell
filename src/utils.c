#include "shell.h"

int readstdin(char* buffer, int bufSize, char* msg)
{
    printf("%s", msg);
    if(fgets(buffer, bufSize, stdin) != NULL)
    {
        if( buffer[strlen(buffer)-1] == '\n')
            buffer[strlen(buffer)-1] = '\0';
    }
    return strlen(buffer);
}

void execcmd(int argc, char* args[])
{
    if(args != 0)
    {
        //test
        if(!strcmp(args[0], "test"))
        {
            printf("Executed test command!\n");
            if(argc > 1)
            {
                for (size_t i = 1; i < argc; i++)
                {
                    printf("%s\n", args[i]);
                }
                
            }
        }

        //exit
        else if(!strcmp(args[0], "exit"))
        {
            pid_t process = getpid();
            kill(process, SIGKILL);
        }

        //info
        else if(!strcmp(args[0], "info"))
        {
            Info();
        }
        else if(!strcmp(args[0], "echo"))
        {
            Echo(args, argc);
        }
        else if(!strcmp(args[0], "exec"))
        {
            Exec(args);
        }
        else if(!strcmp(args[0], "help"))
        {
            HelpMsg();
        }
        else if(!strcmp(args[0], "cd"))
        {
            cd(args);
        }
        else if(!strcmp(args[0], "pwd"))
        {
            char cwd[MAX_INPUT_SIZE];getcwd(cwd, MAX_INPUT_SIZE);
            printf("%s\n", cwd);
        }
        else if(!strcmp(args[0], "ls"))
        {
            ls(args);
        }
        else if(!strcmp(args[0], "size"))
        {
            size(args);
        }
        else if(!strcmp(args[0], "clear") || !strcmp(args[0], "clr"))
        {
            printf("\033[H\033[J");
        }
        else
        {
            fprintf(stderr, "pizshell: %s: command not found\nrun help to see list of commands\n", args[0]);
        }
    }
    else
    {
        perror("invalid (char*)args");
        exit(1);
    }
}