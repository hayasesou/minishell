#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pipex
{
    int input_fd;
    int output_fd;
    int pipefd[2];
} t_pipex;


int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    (void)argc;
    (void)argv;
    (void)envp;

    if (pipe(pipex.pipefd) == -1)
        exit(1);

    printf("pipefd[0]: %d\n", pipex.pipefd[0]);
    printf("pipefd[1]: %d\n", pipex.pipefd[1]);

    return 0;
}