#include "minishell.h"

void	fatal_error(char *msg)
{
    ft_putstr_fd("Fatal Error: ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
	exit(1);
}
