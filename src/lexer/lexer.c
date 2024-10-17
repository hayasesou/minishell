#include "minishell.h"

void	check_token_operation(t_context *ctx)
{
	t_token	*current;

	current = ctx->token_head;
	while (current->type != TK_EOF)
	{
		if ((current->type == TK_REDIR_IN
				|| current->type == TK_REDIR_OUT
				|| current->type == TK_REDIR_APPEND
				|| current->type == TK_REDIR_HEREDOC
				|| current->type == TK_PIPE)
			&& current->next->type == TK_EOF)
		{
			free_token(&ctx->token_head);
			ft_printf("syntax error near unexpected token `newline'\n");
			ctx->exit_status = 2;
			ctx->token_head = NULL;
			return ;
		}
		current = current->next;
	}
}

void lexer(t_context *ctx, char *line)
{
    t_token *token;
    bool    space_before;
    t_token *token_head;

    token = token_init(ctx);
    space_before = false;
    token_head = token;
    while (*line && is_blank(*line))
        line++;
    while (*line)
    {
        if (is_blank(*line))
        {
            space_before = true;
            line++;
            continue;
        }
        else if (is_operator(*line))
        {
            operator(&line, line, token);
            space_before = false;
        }
        else if (is_quote(*line))
        {
            quote(&line, line, token, space_before);
            space_before = false;
        }
        else
        {
            word(&line, line, token, space_before);
            space_before = false;
        }
        if (token->next)
            token = token->next;
    }
    token_node_add(token, token_node_create("", TK_EOF));
	check_token_operation(ctx);
	if (ctx->token_head == NULL)
		return ;
    expansion(token_head,  ctx);
}
