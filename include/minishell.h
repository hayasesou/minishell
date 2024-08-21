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
#include <sys/wait.h>
#include <sys/stat.h>

# include "libft.h"
# include "struct.h"
# include "lexer.h"
# include "redirect.h"
# include "builtin.h"


//exit_status
# define NORMAL_ERROR 1
# define ERROR_TOKENIZE 258
# define COMMAND_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define IS_DIR 126

extern bool	syntax_error;

void	todo(const char *msg) __attribute__((noreturn));

// error
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);

// env
t_env	*node_new_set(t_env *env_node, char *str);
t_env	*node_new(char *str);
t_env	*env_head_init(void);
t_env	*env_init(char **envp);
char ** make_env_list(t_env *env_head, t_context *context);
void free_env_list(char **env_list);
void free_all_env_node(t_env *env_head);

// main
void	main_loop(t_context *ctx, char *line);
t_context	*minishell_init(int ac, char **av, char **envp);
int	exec(char argv[]);
void	validate_access(const char *path, const char *filename);
char	*search_path(const char *filename);

#endif