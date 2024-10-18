/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:34:30 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:35:02 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_parser *parser, t_context *context)
{
	t_env	*env_tmp;

	if (parser->cmd[1] != NULL)
	{
		ft_printf("minishell: env: %s: No such file or directory\n",
			parser->cmd[1]);
		context->exit_status = NORMAL_ERROR;
		exit(EXIT_FAILURE);
	}
	env_tmp = context->env_head->next;
	while (env_tmp != context->env_head)
	{
		ft_printf("%s=%s\n", env_tmp->env_name, env_tmp->env_val);
		env_tmp = env_tmp->next;
	}
}
