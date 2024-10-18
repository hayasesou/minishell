/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:18 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:44:19 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_string(t_token *token)
{
	if (token->type == TK_WORD || token->type == TK_SINGLE_QUOTE
		|| token->type == TK_DOUBLE_QUOTE || token->type == TK_SPACE_WORD
		|| token->type == TK_SPACE_SINGLE_QUOTE
		|| token->type == TK_SPACE_DOUBLE_QUOTE)
		return (true);
	return (false);
}

bool	is_not_space_string(t_token *token)
{
	if (token->type == TK_WORD || token->type == TK_SINGLE_QUOTE
		|| token->type == TK_DOUBLE_QUOTE)
		return (true);
	return (false);
}

bool	is_redirect(t_token *token)
{
	if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT
		|| token->type == TK_REDIR_APPEND || token->type == TK_REDIR_HEREDOC)
		return (true);
	return (false);
}
