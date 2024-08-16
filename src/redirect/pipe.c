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

    // // 9 is the length of "/usr/bin/"
    char *cmd_path = ft_strjoin("/usr/bin/", tmp_parser->cmd[0]);
    execve(cmd_path, tmp_parser->cmd, NULL);
    free(cmd_path);
    printf("execve error\n");
    close(pipe_x->stdin_fd);
    close(pipe_x->stdout_fd);
    exit(1);
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
        // Parent process
        if (pipe_x.current_cmd_num > 0)
        {
            close(pipe_x.pipe_fd[pipe_x.current_cmd_num - 1][READ]);
            close(pipe_x.pipe_fd[pipe_x.current_cmd_num - 1][WRITE]);
        }
        close_heredoc_fds(tmp_parser);
        pipe_x.current_cmd_num++;
        tmp_parser = tmp_parser->next;
    }


    int i = 0;
    while(i < pipe_x.current_cmd_num)
    {
        waitpid(pipe_x.pids[i], NULL, 0);
        i++;
    }
    dup2(pipe_x.stdin_fd, STDIN_FILENO);
    dup2(pipe_x.stdout_fd, STDOUT_FILENO);
    close(pipe_x.stdin_fd);
    close(pipe_x.stdout_fd);
    tmp_parser = parser_head;
    free_pipex(tmp_parser, &pipe_x);
}



#include <unistd.h>

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

    // << eof > test2 > test3
    // t_file f11;
    // t_file f12;
    // t_file f13;
    // f11.file_name = "test1";
    // f11.type = HEREDOC;
    // f11.heredoc_fd = -1;
    // f11.next = &f12;
    // f12.file_name = "test2";
    // f12.type = HEREDOC;
    // f12.heredoc_fd = -1;
    // f12.next = &f13;
    // f13.file_name = "test3";
    // f13.type = HEREDOC;
    // f13.heredoc_fd = -1;
    // f13.next = NULL;


    // parser_head[0].file = &f11;
    
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
    return 0;
}
