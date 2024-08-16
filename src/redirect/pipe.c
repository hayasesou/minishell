#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>





#define SUCESS 0


void process_heredoc(t_parser *parser_head, t_context *context)
{
    t_parser *tmp_parser;
    int status;
    t_file *file;

    tmp_parser = parser_head;
    status = SUCESS;
    while(tmp_parser != NULL)
    {
       file = tmp_parser->file;
       while(file != NULL)
       {
           if (file->type == HEREDOC)
           {
                file->heredoc_fd = heredoc(file, context, &status);
           }
           else if(file->type == QUOTE_HEREDOC)
           {
                file->heredoc_fd = quote_heredoc(file, context, &status);
           }
           file = file->next;
       }
        tmp_parser = tmp_parser->next;
    }
}

void setup_heredoc_fd(t_parser *parser)
{
    t_file *file = parser->file;
    while(file != NULL)
    {
        if (file->type == HEREDOC || file->type == QUOTE_HEREDOC)
        {
            dup2(file->heredoc_fd, STDIN_FILENO);
            close(file->heredoc_fd);
        }
        file = file->next;
    }
}

void close_heredoc_fds(t_parser *parser)
{
    t_file *file = parser->file;
    while(file != NULL)
    {
        if (file->type == HEREDOC || file->type == QUOTE_HEREDOC)
        {
            close(file->heredoc_fd);
        }
        file = file->next;
    }
}


// Implementation of the minishell_pipe function
void minishell_pipe(t_parser *parser_head, t_context *context)
{
    (void)context;
    t_pipex pipe_x;
    t_parser *tmp_parser;
    int status;

    tmp_parser = parser_head;
    status = SUCESS;
    init_pipex(tmp_parser, &pipe_x);
    // Here you can add the actual process handling logic

    process_heredoc(tmp_parser, context);

    int cmd_num;
    cmd_num = 0;
    while(tmp_parser != NULL)
    {
        if (tmp_parser->next != NULL)
            pipe(pipe_x.pipe_fd[cmd_num]);
        
        pipe_x.pids[cmd_num] = fork();
        pipe_x.last_cmd_pid = pipe_x.pids[cmd_num];

        if (pipe_x.pids[cmd_num] == 0)
        {
            if (tmp_parser->prev != NULL)
                prev_pipe(&pipe_x, cmd_num);
            if(tmp_parser->next != NULL)
                next_pipe(&pipe_x, cmd_num);
            if (tmp_parser->file != NULL)
                redirect(tmp_parser, context, &status);


            setup_heredoc_fd(tmp_parser);


            for (int i = 0; i < cmd_num; i++)
            {
                close(pipe_x.pipe_fd[i][READ]);
                close(pipe_x.pipe_fd[i][WRITE]);
            }
            // // 9 is the length of "/usr/bin/"
            char *cmd_path = ft_strjoin("/usr/bin/", tmp_parser->cmd[0]);
            execve(cmd_path, tmp_parser->cmd, NULL);
            free(cmd_path);
            printf("execve error\n");
            close(pipe_x.stdin_fd);
            close(pipe_x.stdout_fd);
            exit(1);
        }
        // Parent process
        if (tmp_parser->prev != NULL)
        {
            close(pipe_x.pipe_fd[cmd_num - 1][READ]);
            close(pipe_x.pipe_fd[cmd_num - 1][WRITE]);
        }

        close_heredoc_fds(tmp_parser);

        cmd_num++;
        tmp_parser = tmp_parser->next;
    }


    // // Wait for the last command to finish
    // waitpid(pipe_x.last_cmd_pid, &status, 0);
    int i = 0;
    while(i < cmd_num)
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



// #include <unistd.h>

// // Example main function for demonstration
// //./pipex cmd1 cmd2
// int main(int ac, char **av)
// {
//     t_context ctx;
//     t_parser *parser_head;
//     int i;

//     parser_head = (t_parser *)malloc(sizeof(t_parser) * (ac - 1));
//     i = 0;
//     while (i < ac - 1)
//     {

//         parser_head[i].cmd = (char **)malloc(sizeof(char *) * 2);
//         parser_head[i].cmd[0] = ft_strdup(av[i + 1]);
//         parser_head[i].cmd[1] = NULL;
//         parser_head[i].file = NULL;
//         if (i == ac - 2)
//             parser_head[i].next = NULL;
//         else
//             parser_head[i].next = &parser_head[i + 1];
//         if (i == 0)
//             parser_head[i].prev = NULL;
//         else
//             parser_head[i].prev = &parser_head[i - 1];
//         i++;
//     }

//     // << eof > test2 > test3
//     t_file f11;
//     t_file f12;
//     t_file f13;
//     f11.file_name = "eof";
//     f11.type = HEREDOC;
//     f11.heredoc_fd = -1;
//     f11.next = &f12;
//     f12.file_name = "test2";
//     f12.type = OUT_FILE;
//     f12.heredoc_fd = -1;
//     f12.next = &f13;
//     f13.file_name = "test3";
//     f13.type = OUT_FILE;
//     f13.heredoc_fd = -1;
//     f13.next = NULL;


//     parser_head[0].file = &f11;
    
//     minishell_pipe(parser_head, &ctx);

//     while(i > 0)
//     {
//         i--;
//         free(parser_head[i].cmd[0]);
//         free(parser_head[i].cmd);
//     }
//     free(parser_head);
//     printf("pid %d\n", getpid());
//     delete_tmpfile();
//     return 0;
// }
