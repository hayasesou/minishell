#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


typedef struct s_pipex
{
    int input_fd;
    int output_fd;
    int pipefd[2];
} t_pipex;




int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;
    pid_t pid1;

    (void)argc;
    (void)argv;
    (void)envp;

    if (pipe(pipex.pipefd) == -1)
        exit(1);
    
    char *file_path = "/usr/bin/ls";
    char *args[] = {"ls", "-l", NULL};

    pid1 = fork();
    if(pid1 == 0)
    {
        printf("child process\n");
        execv(file_path, args);
        printf("execv failed\n");
    }
    else
    {
        waitpid(pid1, NULL, 0);
        printf("parent process\n");
    }

    return 0;
}