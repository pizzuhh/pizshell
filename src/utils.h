#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include <pwd.h>

int readstdin(char* buffer, int bufSize, char* msg);
char* xor(char* data, char key[], size_t data_size);
size_t writefile(char* path, char* data);
char* readfile(char* path);
