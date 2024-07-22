#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    pid_t fork_pid;
    char * file_name = "fork_sharing_file.txt";
    int fd;

    fork_pid = fork();
    //#### if you add O_TRUNC , you can write to file_name as clean state
    // fd = open(file_name, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);

    fd = open(file_name, O_RDWR | O_APPEND | O_CREAT , S_IREAD | S_IWRITE);
    printf("fork_pid: %d\n", fork_pid);
    if (fork_pid == -1)
    {
        perror("fork");
        return 1;
    }
    if(fork_pid != 0)
    {
        wait(0);
        write(fd, "parent process\n", 15);
    }
    else
    {
        write(fd, "child process\n", 14);
    }

    return 0;
}