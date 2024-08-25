#ifndef ERROR_H
# define ERROR_H

void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	todo(const char *msg);
void	tokenize_error(const char *location, char **rest, char *line);

#endif