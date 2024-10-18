/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:00 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:29:36 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word(char **line_ptr, char *line, t_token *token, bool space_before)
{
	char	*start;
	char	*word;

	start = line;
	while (*line && is_word(*line))
		line++;
	word = ft_strndup(start, line - start);
	if (word == NULL)
		fatal_error("tokenize: word strndup error");
	*line_ptr = line;
	if (space_before == true)
		token_node_add(token, token_node_create(word, TK_SPACE_WORD));
	else
		token_node_add(token, token_node_create(word, TK_WORD));
	free(word);
}
