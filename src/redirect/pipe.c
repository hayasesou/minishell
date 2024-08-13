#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct s_pipex
{
    pid_t *pids; // array of pid. the count of pid is equal to cmd count
    int **pipe_fd;  // array of pipe_fd. the count of pipe_fd is equal to cmd count - 1
} t_pipex;

// Initialize process and pipe_fd arrays
void init_pipex(t_parser *parser_head, t_pipex *pipe_x)
{
    t_parser *tmp_parser;
    int count;
    int i;

    count = 0;
    tmp_parser = parser_head;
    while (tmp_parser != NULL)
    {
        count++;
        tmp_parser = tmp_parser->next;
    }

    pipe_x->pids = (pid_t *)malloc(sizeof(pid_t) * count);
    if (pipe_x->pids == NULL)
        fatal_error("malloc error\n");

    pipe_x->pipe_fd = (int **)malloc(sizeof(int *) * (count - 1));
    if (pipe_x->pipe_fd == NULL)
    {
        free(pipe_x->pids);
        fatal_error("malloc error\n");
    }

    i = 0;
    tmp_parser = parser_head;
    while (i < count - 1)
    {
        pipe_x->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
        if (pipe_x->pipe_fd[i] == NULL)
        {
            while (i > 0)
            {
                i--;
                free(pipe_x->pipe_fd[i]);
            }
            free(pipe_x->pipe_fd);
            free(pipe_x->pids);
            fatal_error("malloc error\n");
        }
        i++;
    }
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

// Implementation of the minishell_pipe function
void minishell_pipe(t_parser *parser_head, t_context *context)
{
    (void)context;
    t_pipex pipe_x;
    t_parser *tmp_parser;

    tmp_parser = parser_head;

    init_pipex(tmp_parser, &pipe_x);
    // Here you can add the actual process handling logic
    tmp_parser = parser_head;
    free_pipex(tmp_parser, &pipe_x);
}



// Example main function for demonstration
//./pipex cmd1 cmd2
int main(int ac, char **av)
{
    t_context ctx;
    t_parser *parser_head;
    int i;

    parser_head = (t_parser *)malloc(sizeof(t_parser) * (ac - 1));
    i = 0;
    while (i < ac - 1)
    {
        parser_head[i].cmd = (char **)malloc(sizeof(char *) * 2);
        parser_head[i].cmd[0] = ft_strjoin("/usr/bin/", av[i + 1]);
        parser_head[i].cmd[1] = NULL;
        if (i == ac - 2)
            parser_head[i].next = NULL;
        else
            parser_head[i].next = &parser_head[i + 1];
        if (i == 0)
            parser_head[i].prev = NULL;
        else
            parser_head[i].prev = &parser_head[i - 1];
        i++;
    }

    minishell_pipe(parser_head, &ctx);

    while(i > 0)
    {
        i--;
        free(parser_head[i].cmd[0]);
        free(parser_head[i].cmd);
    }
    free(parser_head);
    return 0;
}
