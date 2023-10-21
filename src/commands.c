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
            execlp(cmd, args[2], args[3]);

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
    "echo:\t\techos text\npwd:\t\tprints the current working dir\ncd:\t\tchanges directory\n"\
    "ls:\t\tlists files in a directory\nsize:\t\tprints the size of a file in bytes\n");
}

void cd(char* args[])
{
    if(chdir(args[1]))
    {
        fprintf(stderr, "error changing dir to %s\nProbably not found or don't have permision!\n", args[1]);
    }
}

void ls(char* args[])
{
    char path[1024];
    //stuff
    if(args[1] == NULL)
        strncpy(path, ".\0", 2);
    else
        strncpy(path, args[1], 1024);
    
    printf("path: %s\n", path);
    //check if path is null
    if(path == NULL)
    {
        printf("path is null!\n");
        return;
    }
    
    //list
    DIR* dir;
    struct dirent *ent;
    dir = opendir(path);
    if (dir == NULL) 
    {
        perror("opendir error\n");
        return;
    }
    while ((ent = readdir(dir)) != NULL) 
    {
        printf("%s ", ent->d_name);
        
    }
    putc('\n', stdout);
    closedir(dir);
}

void size(char* args[])
{
    char* file = args[1];
    char* path = realpath(file, 0);
    char* arg = args[2];
    FILE* f = fopen(path, "r");
    if(!f)
    {
        printf("fopen() error: file not found\n");
    }
    fseek(f, 0L, SEEK_END);
    size_t size = ftell(f);

    if(arg != NULL)
        printf("%s: %ldbytes\n", (!strcmp(arg, "-f")||!strcmp(arg, "--full")) ? path : file, size);
    else
        printf("%s: %ldbytes\n", file, size);
}
