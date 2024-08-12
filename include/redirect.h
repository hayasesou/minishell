#ifndef REDIRECT_H
# define REDIRECT_H

#include <fcntl.h>
#include "minishell.h"


// #define HEREDOCTMP "/tmp/.heredoctmp"
#define HEREDOCTMP ".heredoctmp"

typedef struct s_heredoc
{
    char *deliminater;
    char *tmpfile;
    int tmpfile_fd;
}   t_heredoc;

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
void create_tmpfile(t_heredoc *heredoc);
void delete_tmpfile(void);

//heredoc_expansion.c
char *heredoc_expantion(char *line, t_context *context);

#endif