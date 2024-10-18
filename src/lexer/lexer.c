#include "minishell.h"

void	fatal_error(char *msg)
{
    ft_putstr_fd("Fatal Error: ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
	exit(1);
}

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
			ft_printf("syntax error near unexpected token `newline'\n"); //　これいるの？
			ctx->exit_status = 2;
			ctx->token_head = NULL;
			return ;
		}
		current = current->next;
	}
}

void    system_check(char *line, t_context *ctx, t_token *token)
{
    if (is_operator(*line))
    {
        operator(&line, line, token, ctx);       
        token->space_before = false;
    }
    else
    {
        quote(&line, line, token, ctx);
        token->space_before = false;
    }
}

void	syntax_error(char *msg, t_context *ctx)
{
    ft_putstr_fd("minishell: syntax error: ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    ctx->sys_error = true;
    ctx->exit_status = SYNTAX_ERROR;
}

void lexer(t_context *ctx, char *line)
{
    t_token *token;
    t_token *token_head;

    token = token_init(ctx);
    token_head = token;
    while (*line && is_blank(*line))
        line++;
    while (*line)
    {
        if (is_blank(*line))
        {
            token->space_before = true;
            line++;
            continue;
        }
        else if (is_operator(*line) || is_quote(*line))
            system_check(line, ctx, token);
        else
        {
            word(&line, line, token, token->space_before);
            token->space_before = false;
        }
        if (ctx->sys_error == true)
        {
            free_token(&ctx->token_head);
            ctx->exit_status = SYNTAX_ERROR;
            ctx->token_head = NULL;
            return ;
        }
        if (token->next)
            token = token->next;
    }
    token_node_add(token, token_node_create("", TK_EOF));
	check_token_operation(ctx);
	if (ctx->token_head == NULL)
		return ;
    // print_lexer(token_head);
    expansion(token_head,  ctx);
}

// void lexer(t_context *ctx, char *line)
// {
//     t_token *token;
//     t_token *token_head;

//     token = token_init(ctx);
//     token_head = token;
//     while (*line && is_blank(*line))
//         line++;
//     while (*line)
//     {
//         if (is_blank(*line))
//         {
//             token->space_before = true;
//             line++;
//             continue;
//         }
//         else if (is_operator(*line) || is_quote(*line))
//         {
//             operator(&line, line, token);
//             space_before = false;
//         }
//         else if (is_quote(*line))
//         {
//             quote(&line, line, token, space_before);
//             space_before = false;
//         }
//         else
//         {
//             word(&line, line, token, space_before);
//             space_before = false;
//         }
//         if (token->next)
//             token = token->next;
//     }
//     token_node_add(token, token_node_create("", TK_EOF));
// 	check_token_operation(ctx);
// 	if (ctx->token_head == NULL)
// 		return ;
//     lexer_print_token(token_head);
//     expansion(token_head,  ctx);
// }
