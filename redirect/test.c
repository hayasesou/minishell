#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int ac, char **av)
{
    int fd1;
    // int fd2;

    char *fd1_text = "This is fd1\n";
    // char *fd2_text = "this is fd2\n";

    if (ac != 2)
    {
        printf("usage: %s <file>\n", av[0]);
        return 1;
    }

    fd1 = open(av[1], O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
    write(fd1, fd1_text, strlen(fd1_text));
    dup2(fd1, 1);
    close(fd1);
    

    write(1, fd1_text, strlen(fd1_text));
    

    return 0;
}