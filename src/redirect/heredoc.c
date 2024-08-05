#include "minishell.h"


char *create_heredoc_file()
{
    int fd;
    fd = open("heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        fatal_error("open error\n");
    }
    return 
}


int heredoc(t_file *file, int *status)
{
    
}