/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:35:26 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:35:27 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_parser *parser, t_context *context, bool is_parent)
{
	if (parser->cmd == NULL)
	{
		ft_printf("minishell: syntax error\n");
		context->exit_status = NORMAL_ERROR;
		exit(EXIT_FAILURE);
	}
	if (is_minishell_builtin(parser->cmd[0]) == true)
	{
		exec_minishell_builtin(parser, context, parser->cmd[0], is_parent);
		exit(EXIT_SUCCESS);
	}
	else
		bash_builtin(parser, context);
	context->exit_status = COMMAND_NOT_FOUND;
	ft_printf("minishell: %s: command not found\n", parser->cmd[0]);
	exit(COMMAND_NOT_FOUND);
}
