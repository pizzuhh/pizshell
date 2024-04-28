#include "shell.h"

int Parse(char* in, char* arg[]) 
{
    char* tok = strtok(strdup(in), " \t");
    int i = 0;
    while (tok != NULL) {
        arg[i] = tok;
        tok = strtok(NULL, " \t");
        i++;
    }
    arg[i] = '\0';  // Null-terminate the argument array
    return i;
}
