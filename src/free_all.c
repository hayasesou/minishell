#include "mini_shell.h"

void free_token(t_token *token)
{
    t_token *tmp;

    while (token)
    {
        tmp = token->next;
        free(token->str);
        free(token);
        token = tmp;
    }
}

void free_all(t_context *ctx)
{
    free_token(ctx->token_head);
    free_parser(ctx->parser_head);
    free_env(ctx->env_head);
    free_ctx(ctx);
}

void    exit_free(t_context *ctx)
{
    free_all(ctx);
    exit(1);
}
