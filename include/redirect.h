#ifndef REDIRECT_H
# define REDIRECT_H

#include <fcntl.h>
#include "minishell.h"


// #define HEREDOCTMP "/tmp/.heredoctmp"
#define HEREDOCTMP ".heredoctmp"
#define READ 0
#define WRITE 1

typedef struct s_heredoc
{
    char *deliminater;
    char *tmpfile;
    int tmpfile_fd;
}   t_heredoc;

typedef struct s_pipex
{
    pid_t *pids; // array of pid. the count of pid is equal to cmd count
    int **pipe_fd;  // array of pipe_fd. the count of pipe_fd is equal to cmd count - 1
    pid_t last_cmd_pid; //bash is execute multiple command by parallel. so, we only need to wait the last command pid
    int stdin_fd;
    int stdout_fd;
    int current_cmd_num;
} t_pipex;


//redirect_output.c
int redirect_output(t_file *file, t_context *context,  int *status);
int append_output(t_file *file, t_context *context,int *status);
bool is_output(t_file *file);

//redirect_input.c
int redirect_input(t_file *file, t_context *context, int *status);
bool is_input(t_file *file);

//redirct_error.c
void error_message(char *file_name);
void unexisted_env_error(char *env);

//heredoc.c
int heredoc(t_file *file, t_context *context, int *status);
int quote_heredoc(t_file *file, t_context *context, int *redirect_status);
void create_tmpfile(t_heredoc *heredoc, t_context *context, int *heredoc_status);
void delete_tmpfile(void);

//heredoc_expansion.c
char *heredoc_expantion(char *line, t_context *context, int *heredoc_status);

//redirect_utils.c
void close_fd(int fd, t_context *context);
void dup2_fd(int old_fd, int new_fd, t_context *context);

//redirect.c
void redirect(t_parser *parser, t_context *context, int *redirect_status);
void builtin_redirect(t_parser *parser, t_context *context, int *redirect_status);

//pipe_utils.c
void prev_pipe(t_pipex *pipe_x, int cmd_num);
void next_pipe(t_pipex *pipe_x, int cmd_num);
void free_pipex(t_parser *parser_head,  t_pipex *pipe_x);
void close_pipe_fd(t_pipex *pipe_x);
void free_single_pipe_fd(t_pipex *pipe_x);

//pipe_struct_init.c
void init_pipex(t_parser *parserm, t_pipex *pipe_x, t_context *context, int  *heredoc_status);

//pipe_heredoc.c
void process_heredoc(t_parser *parser, t_context *context, int *heredoc_status);
void setup_heredoc_fd(t_parser *parser);
void close_heredoc_fds(t_parser *parser);

//pipe_error.c
void pipe_check(t_pipex *pipex, t_context *context, int *status, int cmd_num);
int fork_check(t_context *context, int *status);


//pipe.c
void minishell_pipe(t_parser *parser_head, t_context *context);

#endif