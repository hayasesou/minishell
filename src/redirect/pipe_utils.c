#include "minishell.h"

void prev_pipe(t_pipex *pipe_x, int cmd_num)
{
    dup2(pipe_x->pipe_fd[cmd_num - 1][READ], STDIN_FILENO);
    close(pipe_x->pipe_fd[cmd_num - 1][READ]);
    close(pipe_x->pipe_fd[cmd_num - 1][WRITE]);
}

void next_pipe(t_pipex *pipe_x, int cmd_num)
{
    dup2(pipe_x->pipe_fd[cmd_num][WRITE], STDOUT_FILENO);
    close(pipe_x->pipe_fd[cmd_num][READ]);
    close(pipe_x->pipe_fd[cmd_num][WRITE]);
}

// Free allocated memory for pipe_fd and pids
void free_pipex(t_parser *parser_head,  t_pipex *pipe_x)
{
    int i;
    int count;
    t_parser *tmp_parser;

    i = 0;
    tmp_parser = parser_head;
    while(tmp_parser != NULL)
    {
        tmp_parser = tmp_parser->next;
        i++;
    }
    count = 0;
    while(count < i - 1)
    {
        free(pipe_x->pipe_fd[count]);
        count++;
    }
    free(pipe_x->pipe_fd);
    free(pipe_x->pids);
}