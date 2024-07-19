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

# define ERROR_TOKENIZE 258
extern bool	syntax_error;

void	todo(const char *msg) __attribute__((noreturn));

// error
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);

#endif