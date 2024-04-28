#include "./utils.h"

int readstdin(char* buffer, int bufSize, char* msg)
{
    printf("%s", msg);
    if(fgets(buffer, bufSize, stdin) != NULL)
    {
        if (buffer == EOF) return 0;
        if( buffer[strlen(buffer)-1] == '\n')
            buffer[strlen(buffer)-1] = '\0';
    } else return -1;
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
        return NULL;

    }
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    if(size < 0)
    {
        fclose(file);
        printf("ftell error\n");
        return NULL;
    }
    fseek(file, 0L, SEEK_SET);
    char* buff = (char*)malloc(sizeof(char)*(size+1));
    if(!buff)
    {
        fclose(file);
        printf("malloc error\n");
        return NULL;
    }

    size_t read_size = fread(buff, 1, size, file);
    fclose(file);

    if (read_size != size) 
    {
        fprintf(stderr, "Error reading file: %s\n", path);
        free(buff);
        return NULL;
    }
    return buff;
}

size_t writefile(char* path, char* data, size_t size)
{
    FILE* file = fopen(path, "w");
    if(!file)
    {
        printf("error opening file: %s\n", path);
        return NULL;
    }
    size_t ret = fwrite(data, 1, size, file);
    fclose(file);
    return ret;
}

size_t fsize(char* path)
{
    FILE* f = fopen(path, "r");
    if(!f)
    {
        printf("fopen() error: file not found\n");
    }
    fseek(f, 0L, SEEK_END);
    size_t size = ftell(f);
    fclose(f);
    return size;
}

