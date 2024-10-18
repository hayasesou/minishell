/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:21:02 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:21:03 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_word(char c)
{
	return (c && !is_operator(c) && !is_quote(c) && !is_blank(c));
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	is_double_quote(char c)
{
	return (c == '\"');
}
