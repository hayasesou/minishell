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

# include "struct.h"
# include "error.h"
# include "lexer.h"
# include "parser.h"

# define ERROR_TOKENIZE 258
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

// main
void	main_loop(t_context *ctx, char *line);
t_context	*minishell_init(int ac, char **av, char **envp);
int	exec(char argv[]);
void	validate_access(const char *path, const char *filename);
char	*search_path(const char *filename);

#endif