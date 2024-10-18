/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:10:25 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:33:05 by hakobaya         ###   ########.fr       */
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

void	system_check(char **line, t_context *ctx, t_token *token)
{
	if (is_operator(**line))
	{
		operator(line, *line, token, ctx);
		token->space_before = false;
	}
	else
	{
		quote(line, *line, token, ctx);
		token->space_before = false;
	}
}

void	lexer(t_context *ctx, char *line)
{
	t_token	*token;
	t_token	*token_head;

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
			continue ;
		}
		else if (is_operator(*line) || is_quote(*line))
			system_check(&line, ctx, token);
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
	expansion(token_head, ctx);
}
