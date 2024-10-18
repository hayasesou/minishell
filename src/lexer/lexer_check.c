/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:33:43 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 04:17:31 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_token_op(t_token *token)
{
	if (token->type == TK_PIPE || token->type == TK_REDIR_IN
		|| token->type == TK_REDIR_OUT || token->type == TK_REDIR_APPEND
		|| token->type == TK_REDIR_HEREDOC)
		return (true);
	return (false);
}

void	syntax_error_operation(char *msg, t_context *ctx)
{
	ft_putstr_fd("minishell: syntax error: near unexpected token ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free_token(&ctx->token_head);
	ctx->token_head = NULL;
	ctx->exit_status = SYNTAX_ERROR;
	ctx->sys_error = true;
}

void	check_token_operation(t_context *ctx)
{
	t_token	*current;

	current = ctx->token_head->next;
	while (current->type != TK_EOF)
	{
		if (is_token_op(current))
		{
			if (is_token_op(current->next))
			{
				syntax_error_operation("", ctx);
				return ;
			}
			else if (current->next->type == TK_EOF)
			{
				syntax_error_operation("'newline'", ctx);
				return ;
			}
		}
		current = current->next;
	}
}
