
#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"

//builtin.c
void exec_cmd(t_parser *parser, t_context *context);

//builtin_minishell.c
bool is_minishell_builtin(char *cmd);

//builtin_bash.c
void bash_builtin(t_parser *parser, t_context *context);

#endif