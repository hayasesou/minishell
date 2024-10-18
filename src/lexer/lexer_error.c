#include "minishell.h"

void	syntax_error(char *msg, t_context *ctx)
{
    ft_putstr_fd("minishell: syntax error: ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    ctx->sys_error = true;
    ctx->exit_status = SYNTAX_ERROR;
}

void	syntax_error_operation(char *msg, t_context *ctx)
{
    ft_putstr_fd("minishell: syntax error: near unexpected token ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    ctx->sys_error = true;
    ctx->exit_status = SYNTAX_ERROR;
}

void syntax_error_unexpected_token(char *unexpected_token, t_context *ctx)
{
    ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
    ft_putstr_fd(unexpected_token, 2);
    ft_putstr_fd("'\n", 2);
    ctx->sys_error = true;
    ctx->exit_status = SYNTAX_ERROR;
}
