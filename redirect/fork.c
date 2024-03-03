#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t fork_pid;
    pid_t my_pid;
    pid_t parent_pid;

    fork_pid = fork();
    if (fork_pid == -1)
    {
        perror("fork");
        return 1;
    }
    my_pid = getpid();
    parent_pid = getppid();
    if(fork_pid == 0)
    {
        printf("fork func return value [%d]\n", fork_pid);
        printf("my_pid [%d]\n", my_pid);
        printf("parent_pid [%d]\n", parent_pid);
        printf("child process\n\n");
        sleep(40);
    }
    else
    {
        // wait(NULL);
        printf("fork func return value [%d]\n", fork_pid);
        printf("my_pid [%d]\n", my_pid);
        printf("parent process\n\n");
        sleep(40);
    }

    return 0;
}