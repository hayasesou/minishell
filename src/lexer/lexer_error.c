/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:37:54 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 04:17:43 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *msg, t_context *ctx)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	ctx->sys_error = true;
	ctx->exit_status = SYNTAX_ERROR;
}

void	syntax_error_unexpected_token(char *unexpected_token, t_context *ctx)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(unexpected_token, 2);
	ft_putstr_fd("'\n", 2);
	ctx->sys_error = true;
	ctx->exit_status = SYNTAX_ERROR;
}
