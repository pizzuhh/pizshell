#include "shell.h"

extern int Parse(char* in, char* arg[]);
extern int readstdin(char* buffer, int bufSize, char* msg);
extern void execcmd(int argc, char* args[]);


void signal_handler(int signum) {
    if (signum == SIGINT) {
        printf("\nRecived CTR+C. The program has been terminated\n");
    } else if (signum == SIGTERM) {
        printf("\nReceived SIGTERM. The program has been terminated.\n");
    }

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

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    char* args = (char*)malloc(sizeof(char)*MAX_INPUT_SIZE);
    //char* arg = "c at";
    while (1)
    {
        if(getuid() == 0)
            readstdin(args, 1024, PROMT_TEXT_ROOT);
        else
            readstdin(args, 1024, PROMT_TEXT_USER);
        if (args[0] == '\0' || isspace(args[0])) {
            // Handle the case of empty input
            continue; // Skip parsing and execution
        }
        char* out[MAX_ARGS];
        int argc = Parse(args, out);
        execcmd(argc, out);
        ZeroMemory(args, 1024);
        
    }
    
    
}