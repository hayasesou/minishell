/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:38:53 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:38:54 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_string(t_token *token, t_context *ctx)
{
	size_t	i;

	i = 0;
	while (token->data[i])
	{
		if (token->data[i] == '$')
		{
			if (!is_env_name_char(token->data[i + 1]) && token->data[i
				+ 1] != '$' && token->data[i + 1] != '?')
				i++;
			else if (!is_heredoc_expansion(token))
				expansion_env(token->data, token, &i, ctx);
			else
				break ;
		}
		else
			i++;
	}
}

static void	expand_value(t_token *token, t_context *ctx)
{
	size_t	i;

	i = 0;
	while (token->data[i])
	{
		if (token->data[i] == '$')
		{
			if (!is_env_name_char(token->data[i + 1]) && token->data[i
				+ 1] != '$' && token->data[i + 1] != '?')
				i++;
			else if (!is_heredoc_expansion(token))
				expansion_env(token->data, token, &i, ctx);
			else
				break ;
		}
		else
			i++;
	}
}

void	expansion(t_token *token_head, t_context *ctx)
{
	t_token	*tmp_token;

	tmp_token = token_head->next;
	while (tmp_token != NULL && tmp_token->type != TK_EOF)
	{
		if (is_double_quote_expansion(tmp_token->type))
			expand_string(tmp_token, ctx);
		else if (is_word_expansion(tmp_token->type))
			expand_value(tmp_token, ctx);
		tmp_token = tmp_token->next;
	}
}
