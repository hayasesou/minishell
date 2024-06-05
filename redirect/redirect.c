#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
    char *path_name;
    FILE *stream;

    if (ac != 3)
    {
        fprintf(stderr, "usage: %s <file>\n", av[0]);
        return (1);
    }
    path_name = (char *)malloc(sizeof(char)  * (strlen(av[1]) + 1));
    path_name = av[1];
    if ((stream = freopen(path_name, "w", stdout)) == NULL)
    {
        fprintf(stderr, "unable to open %s\n", path_name);
        return (1);
    }

    fprintf(stdout, "%s", av[2]);
    fclose(stream);

    return (0);
}