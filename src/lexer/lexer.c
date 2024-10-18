/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:10:25 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 23:34:11 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	consume_blank(char **line_ptr, t_token *token)
{
	bool	consumed;

	consumed = false;
	while (**line_ptr && is_blank(**line_ptr))
	{
		token->space_before = true;
		(*line_ptr)++;
		consumed = true;
	}
	return (consumed);
}

void	lexer_exec(t_context *ctx, t_token **token_ptr, char **line_ptr)
{
	t_token	*token;
	char	*line;

	token = *token_ptr;
	line = *line_ptr;
	while (*line && (ctx->sys_error == false))
	{
		if (consume_blank(&line, token))
			continue ;
		else if (is_operator(*line) || is_quote(*line))
			system_check(&line, ctx, token);
		else
		{
			word(&line, line, token, token->space_before);
			token->space_before = false;
		}
		if (ctx->sys_error == true)
			return ;
		if (token->next)
			token = token->next;
	}
	*token_ptr = token;
	*line_ptr = line;
}

void	lexer(t_context *ctx, char *line)
{
	t_token	*token;
	t_token	*token_head;

	token = token_init(ctx);
	token_head = token;
	while (*line && is_blank(*line))
		line++;
	lexer_exec(ctx, &token, &line);
	if (ctx->sys_error == true)
	{
		free_token(&ctx->token_head);
		ctx->exit_status = SYNTAX_ERROR;
		ctx->token_head = NULL;
		return ;
	}
	token_node_add(token, token_node_create("", TK_EOF));
	check_token_operation(ctx);
	if (ctx->token_head == NULL)
		return ;
	expansion(token_head, ctx);
}
