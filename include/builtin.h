
#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"

//builtin.c
void exec_cmd(t_parser *parser, t_context *context);

//builtin_minishell.c
bool is_minishell_builtin(char *cmd);
void exec_minishell_builtin(t_parser *parser, t_context *context, char *cmd);

//builtin_bash.c
void bash_builtin(t_parser *parser, t_context *context);


//builtin_cd.c
void cd_builtin(t_parser *parser, t_context *context);

//builtin_pwd.c
void pwd_builtin(t_context *context);

#endif