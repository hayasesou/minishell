/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:46:04 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:46:06 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect_type	get_redirect_type(t_token_type type)
{
	if (type == TK_REDIR_IN)
		return (IN_FILE);
	else if (type == TK_REDIR_OUT)
		return (OUT_FILE);
	else if (type == TK_REDIR_APPEND)
		return (APPEND);
	else if (type == TK_REDIR_HEREDOC)
		return (HEREDOC);
	else
		return (UNKNOWN);
}
