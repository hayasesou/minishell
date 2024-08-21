#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

#define SUCESS 1


static void child_process(t_parser *tmp_parser, t_pipex *pipe_x, t_context *context, int *status)
{
    if (tmp_parser->prev != NULL)
        prev_pipe(pipe_x, pipe_x->current_cmd_num);
    if(tmp_parser->next != NULL)
        next_pipe(pipe_x, pipe_x->current_cmd_num);
    redirect(tmp_parser, context, status);
    setup_heredoc_fd(tmp_parser);
    exec_cmd(tmp_parser, context);
}


static void wait_child_and_close_pipe(t_parser *parser, t_pipex *pipe_x)
{
    int i = 0;
    while(i < pipe_x->current_cmd_num)
    {
        waitpid(pipe_x->pids[i], NULL, 0);
        i++;
    }
    dup2(pipe_x->stdin_fd, STDIN_FILENO);
    dup2(pipe_x->stdout_fd, STDOUT_FILENO);
    close(pipe_x->stdin_fd);
    close(pipe_x->stdout_fd);
    free_pipex(parser, pipe_x);
}


// Implementation of the minishell_pipe function
void minishell_pipe(t_parser *parser_head, t_context *context)
{
    t_pipex pipe_x;
    t_parser *tmp_parser;
    int status;

    tmp_parser = parser_head;
    status = SUCESS;
    init_pipex(tmp_parser, &pipe_x, context, &status);
    process_heredoc(tmp_parser, context, &status);

    while(tmp_parser != NULL)
    {
        if (tmp_parser->next != NULL)
            pipe_check(&pipe_x, context, &status, pipe_x.current_cmd_num);
        pipe_x.pids[pipe_x.current_cmd_num] = fork_check(context, &status);
        pipe_x.last_cmd_pid = pipe_x.pids[pipe_x.current_cmd_num];

        if (pipe_x.pids[pipe_x.current_cmd_num] == 0)
            child_process(tmp_parser, &pipe_x, context, &status);
        if (pipe_x.current_cmd_num > 0)
            close_pipe_fd(&pipe_x);
        close_heredoc_fds(tmp_parser);
        pipe_x.current_cmd_num++;
        tmp_parser = tmp_parser->next;
    }
    wait_child_and_close_pipe(parser_head, &pipe_x);
}



#include <unistd.h>

// Example main function for demonstration
//./pipex cmd1 cmd2
int main(int ac, char **av, char **envp)
{
    t_context ctx;
    t_parser *parser_head;
    int i;

    parser_head = (t_parser *)malloc(sizeof(t_parser) * (ac - 1));
    ctx.env_head = env_init(envp);
    i = 0;
    while (i < ac - 1)
    {

        parser_head[i].cmd = (char **)malloc(sizeof(char *) * 2);
        parser_head[i].cmd[0] = ft_strdup(av[i + 1]);
        parser_head[i].cmd[1] = NULL;
        parser_head[i].file = NULL;
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

    // if(ac > 2)
    // {
    // // << eof > test2 > test3
    // t_file f11;
    // t_file f12;
    // t_file f13;
    // f11.file_name = "eof";
    // f11.type = HEREDOC;
    // f11.heredoc_fd = -1;
    // f11.next = &f12;
    // f12.file_name = "test2";
    // f12.type = OUT_FILE;
    // f12.heredoc_fd = -1;
    // f12.next = &f13;
    // f13.file_name = "test3";
    // f13.type = OUT_FILE;
    // f13.heredoc_fd = -1;
    // f13.next = NULL;


    // parser_head[0].file = &f11;
    // }

    // //cmd | cmd < eof
    // if (ac > 3)
    // {
    //     t_file f21;
    //     f21.file_name = "eof2";
    //     f21.type = HEREDOC;
    //     f21.heredoc_fd = -1;
    //     f21.next = NULL;
    //     parser_head[1].file = &f21;
    // }

    minishell_pipe(parser_head, &ctx);

    while(i > 0)
    {
        i--;
        free(parser_head[i].cmd[0]);
        free(parser_head[i].cmd);
    }
    free(parser_head);
    printf("pid %d\n", getpid());
    delete_tmpfile();
    free_all_env_node(ctx.env_head);
    return 0;
}
