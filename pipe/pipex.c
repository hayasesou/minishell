#include <unistd.h>
#include <stdio.h>
#include <sysy/type.h>

typedef struct s_pipex
{
    int input_fd,
    int output_fd,
    int pipefd[2],
} t_pipex;





int main(int argc, char **argv, char **envp)
{
    t_piepx pipex;

    if (argc != 5)
    {
        printf("Error: invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }
    pipex.inputfd = open(argv[1], O_RDONLY);
    if (pipex.inutfd < 0)
    {
        printf("Error: open error")
        eixt(EXIT_FAILURE)
    }
    pipex.outputfd _ open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex.outpfd <0)
    {
        close(pipex.inputfd);
        printf("Error: open error")
        exit(EXIT_FALURE);
    }
    
}

close()