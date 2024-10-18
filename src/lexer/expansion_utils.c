/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:40:27 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:40:28 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_double_quote_expansion(t_token_type type)
{
	return (type == TK_DOUBLE_QUOTE || type == TK_SPACE_DOUBLE_QUOTE);
}

bool	is_word_expansion(t_token_type type)
{
	return (type == TK_WORD || type == TK_SPACE_WORD);
}

char	*ft_strjoin_all(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}
