/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:35:33 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:35:34 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_builtin(t_parser *parser, t_context *context)
{
	if (parser->cmd == NULL)
		return ;
	else if (parser->cmd[1] == NULL)
		no_arg_export(context->env_head);
	else
		arg_export(context->env_head, parser->cmd[1], context);
}
