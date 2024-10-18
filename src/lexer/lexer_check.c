/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:33:43 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 23:36:58 by hakobaya         ###   ########.fr       */
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
				syntax_error_operation("\n", ctx);
				return ;
			}
			else if (current->next->type == TK_EOF)
			{
				syntax_error_operation("'newline'\n", ctx);
				return ;
			}
		}
		current = current->next;
	}
}
