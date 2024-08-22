#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "./libft/libft.h"

typedef struct s_pipex
{
    int input_fd;
    int output_fd;
    int pipefd[2];
    char **envp;
}   t_pipex;

char **ft_split(char const *s, char c);
