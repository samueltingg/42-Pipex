#include "../includes/pipex.h"

int main(int argc, char **argv, char **env)
{
    int i;
    (void)argc;
    (void)argv;
    i = -1;
    while (env[++i])
    {
        printf("%s\n", env[i]);    
    }
}