#include "../include/minishell.h"

bool	syntax_error = false;

void	fatal_error(const char *msg) __attribute__((noreturn));

void	assert_error(const char *msg) __attribute__((noreturn));
// attributeを関数につけると、「この関数はreturnしない（≒この関数が呼ばれたときはプログラムが終了する）」ということをコンパイラに知らせる

void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

void	assert_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	err_exit(const char *location, const char *msg, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg);
	exit(status);
}

void	todo(const char *msg)
{
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	syntax_error = true;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	while (*line)
		line++;
	*rest = line;
}



