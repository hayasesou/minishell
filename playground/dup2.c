#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// how to use
// $ cc dup2.c && ./a.out test.txt

int main(int ac, char **av)
{
    int fd1;
    int fd2;

    char *fd1_text = "this is fd1\n";
    char *fd2_text = "this is fd2\n";

    if (ac != 2)
    {
        fprintf(stderr, "usage: %s <file>\n", av[0]);
        return (1);
    }
    
    // ファイルを開いてそこに文字列を書き込む
    fd1 = open(av[1], O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
    write(fd1, fd1_text, strlen(fd1_text));

    // dup2の使用
    fd2 = dup2(fd1, 1);
    write(fd2, fd2_text, strlen(fd2_text));
    write(1, "hello world\n", 12);

    close(fd1);
    close(fd2);

    return (0);
}