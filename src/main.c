#include "shell.h"

extern int Parse(char* in, char* arg[]);
extern int readstdin(char* buffer, int bufSize, char* msg);
extern void execcmd(int argc, char* args[]);


void signal_handler(int signum) {
    if (signum == SIGINT) {
        //printf("\nRecived CTR+C. The program has been terminated\n");
        //exit(0);
    } else if (signum == SIGTERM) {
        printf("\nReceived SIGTERM. The program has been terminated.\n");
    }
    remove("./tmphis");
    exit(0);
}


int main()
{

    if(ENABBLE_ROOT == 0)
    {
        if(getuid() == 0)
        {
            perror("ROOT IS DISABLED!\n");
            exit(-1);
        }
    }

    if(ENABLE_WELCOME == 1)
        printf("[pizshell v%s]\n", VESRSION);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    char* args = (char*)malloc(sizeof(char)*MAX_INPUT_SIZE);
    FILE* tmp = fopen(".pizshell_history", "a+");
    while (1)
    {
        int readstdingval = 0;
        if(getuid() == 0)
            readstdingval = readstdin(args, 1024, PROMT_TEXT_ROOT);
        else
            readstdingval = readstdin(args, 1024, PROMT_TEXT_USER);
        
        if (readstdingval < 0) exit(2);
        if (args[0] == '\0' || isspace(args[0]))
            continue;
        //write to tmp history file test
        char* out[MAX_ARGS];
        int argc = Parse(args, out);
        if (argc <= 0) continue;
        execcmd(argc, out);
        for (size_t i = 0; i < argc; i++)
        {
            fwrite(out[i], 1, strlen(out[i]), tmp);
            putc(' ', tmp);
        }
        fputc('\n', tmp);
        fflush(tmp);
        ZeroMemory(args, 1024);
        
    }
    
    fclose(tmp);
    // remove("./.pizshell_history");
}
