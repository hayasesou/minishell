
#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// builtin.c
void	exec_cmd(t_parser *parser, t_context *context, bool is_parent);

// builtin_minishell.c
bool	is_minishell_builtin(char *cmd);
void	exec_minishell_builtin(t_parser *parser, t_context *context, char *cmd,
			bool is_parent);

// builtin_bash.c
void	bash_builtin(t_parser *parser, t_context *context);

// builtin_cd.c
void	cd_builtin(t_parser *parser, t_context *context);

// builtin_pwd.c
void	pwd_builtin(t_context *context);

// builtin_export.c
void	export_builtin(t_parser *parser, t_context *context);

// builtin_export_utils.c
void	no_arg_export(t_env *env_head);
void	arg_export(t_env *env_head, char *arg, t_context *context);

// builtin_echo.c
void	echo_builtin(t_parser *parser, t_context *context);

// builtin_env.c
void	env_builtin(t_parser *parser, t_context *context);

// builtin_unset.c
void	unset_builtin(t_parser *parser, t_context *context);

// builtin_exit.c
void	exit_builtin(t_parser *parser, t_context *context, bool is_parent);
void	ft_puterr(char *str);
bool	overflow_check(long num, int num2, int flag);
bool	is_overflow(char *str);
bool	is_valid_number(const char *str);
void	cleanup_and_exit(t_context *context, int exit_status);

#endif