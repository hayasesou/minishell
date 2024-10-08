#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# include "libft.h"
# include "ft_printf.h"
# include "struct.h"
# include "error.h"
# include "lexer.h"
# include "parser.h"
# include "redirect.h"
# include "builtin.h"

#define SUCCESS 1
#define LAST_CMD_PID 0
#define SPECIFIED_DIR 1
//exit_status
# define NORMAL_EXIT 0
# define NORMAL_ERROR 1
# define ERROR_TOKENIZE 258
# define COMMAND_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define IS_DIR 126

extern bool   syntax_error;
extern int    g_signal;

void	todo(const char *msg) __attribute__((noreturn));

// error
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);

// env
t_env	*node_new_set(t_env *env_node, char *str);
t_env	*node_new(char *str);
void	node_add(t_env *head, t_env *new);
t_env	*env_head_init(void);
t_env	*env_init(char **envp);

//env_utils.c
char ** make_env_list(t_env *env_head, t_context *context);
void free_env_list(char **env_list);
void free_all_env_node(t_env *env_head);
char *get_env_value(char *env_name, t_env *env_head);
char  *heredoc_get_env_value(char *env_name, t_env *env_head, t_context *context, int *heredoc_status);
void set_env_value(char *env_name, char *new_env_value, t_env *env_head, t_context *context);
char *find_first_equal(char *str);
char *ft_strndup(char *str, size_t n);

// signal
void    signal_init(t_context *ctx);
void    set_signal_handler();
void	set_signal_parent_handler();
void    set_signal_child_handler();
void    set_heredoc_signal_parent_handler();
void    set_heredoc_signal_child_handler();
void	signal_handler(int signum);
void    signal_parent_handler(int signum);
void	heredoc_signal_parent_handler(int signum);

// free
void free_token(t_token *head);
void free_parser(t_parser *head);
void free_env_node(t_env *node);
void free_env(t_env *head);

// main
void	main_loop(t_context *ctx, char *line);
t_context	*minishell_init(int ac, char **av, char **envp);
void signal_init(t_context *ctx);
int	exec(char argv[]);
void	validate_access(const char *path, const char *filename);
char	*search_path(const char *filename);

#endif