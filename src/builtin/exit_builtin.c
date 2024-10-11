#include "minishell.h"

static void    exit_with_error(char *msg, int exit_code, char **args, t_context *ctx)
{
    ft_puterr("exit\n");
    ft_puterr("minishell: exit: ");
    ft_puterr(msg);
    ft_puterr("\n");
    free_all(ctx);
    ctx->exit_status = exit_code;
    exit(exit_code);
}

void    exit_builtin()
{
    ft_printf("exit\n");
    exit(0);
}