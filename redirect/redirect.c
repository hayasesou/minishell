#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char * path_name  = "test.txt";
    FILE *stream;

    if ((stream = freopen(path_name, "w", stdout)) == NULL)
    {
        fprintf(stderr, "unable to open %s\n", path_name);
        return (1);
    }
    fprintf(stdout, "this is a test\n");
    fclose(stream);

    return (0);
}