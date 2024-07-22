#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


// fork() make a new process by copying the current process.
// The new process is called the child process, and the original process is called the parent process.
// return value of fork() is the pid of the child process in the parent process, and 0 in the child process.
// by using the wait(), the parent process cant wait for the child process to finish.

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
        sleep(3);
    }
    else
    {
        wait(NULL);
        printf("fork func return value [%d]\n", fork_pid);
        printf("my_pid [%d]\n", my_pid);
        printf("parent process\n\n");
    }

    return 0;
}