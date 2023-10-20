#include "shell.h"
#include "commmands.h"

void Info(void)
{
    pid_t pid = getpid();
    char cwd[MAX_INPUT_SIZE];getcwd(cwd, MAX_INPUT_SIZE);
    char* usr = getlogin();
    uid_t uid = getuid();
    gid_t gid = getgid();
    printf("Current pID: %d\nCurrent path: %s\nCurrent user: %s\nCurrent uid and gid: (uid)%d (gid)%d\n",
    pid, cwd, usr, uid, gid);
}

void Echo(char* args[], int argc)
{
    for (size_t i = 1; i < argc; i++)
    {
        printf("%s ", args[i]);
    }
    fputc('\n', stdout);
}

int Exec(char* args[])
{
    char* cmd = args[1];
    

    pid_t pid = fork();

        if (pid == 0) {
            // Child process
            execlp(cmd, args, NULL);

            // If execlp fails, print an error message
            perror("Error");
            return 1;
        } else if (pid < 0) {
            // Forking failed
            perror("Fork failed");
        } else {
            // Parent process
            wait(NULL);
        }
        return 0;
}

void HelpMsg(void)
{
    printf("pizhell help:\ntest:\t\ttest command\ninfo:\t\tdisplays some info\n"\
    "exec:\t\texecutes application from the PATH variable\nexit:\t\texits the shell\n"\
    "echo:\t\techos text\n");
}

void cd(char* args[])
{
    if(chdir(args[1]))
    {
        fprintf(stderr, "error changing dir to %s\nProbably not found or don't have permision!\n", args[1]);
    }
}