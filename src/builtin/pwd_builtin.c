#include "minishell.h"

void pwd_builtin(t_context *context)
{
    char *pwd;

    pwd = get_env_value("PWD", context->env_head);
    if (pwd == NULL)
    {
        context->exit_status = NORMAL_ERROR;
        perror("minishell pwd");
        return ;
    }
    ft_printf("%s\n", pwd);
    free(pwd);
    context->exit_status = NORMAL_EXIT;
}
