#include "shell.h"
#include "utils.h"

void Info(void); // Displays short info about the process, current working directory and the user
void Echo(char* args[], int argc); // echos text to the stdout
int Exec(char* args[]); // executes files from the $PATH variable
void HelpMsg(char* args[]); // help command
void cd(char* args[]); // chande dir command
void ls(char* args[]); // lists files in a directory
void size(char* args[]); // prints the size of file in bytes
void cat(char* args[]); // concatenate files and print on the standard output
void xr(char* args[]);