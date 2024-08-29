#include "minishell.h"

void error_message(char *file_name)
{
    ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
}

void unexisted_env_error(char *env)
{
    ft_printf("minishell: %s: ambiguous redirect\n", env);
}