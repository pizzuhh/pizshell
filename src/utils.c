#include "./utils.h"

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

char* xor(char* data, char key[], size_t data_size)
{
    size_t key_size = strlen(key);
    char* out = (char*)malloc(sizeof(char)*data_size);
    for (size_t i = 0; i < data_size; i++)
    {
        out[i] = data[i] ^ key[i % key_size];
    }
    return out;
}

char* readfile(char* path)
{
    FILE* file = fopen(path, "r");
    if(!file)
    {
        printf("error opening file: %s\n", path);
        return "ERR_FOPEN";
    }
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char* buff = (char*)malloc(sizeof(char)*size);

    fread(buff, size, 1, file);
    return buff;
}

size_t writefile(char* path, char* data)
{
    FILE* file = fopen(path, "w");
    if(!file)
    {
        printf("error opening file: %s\n", path);
        return "ERR_FOPEN";
    }
    
    return fwrite(data, strlen(data)+1, 1, file);
}