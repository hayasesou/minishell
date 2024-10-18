/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:35:35 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:35:36 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_context *context)
{
	char	*pwd;

	pwd = get_env_value("PWD", context->env_head);
	if (pwd == NULL)
	{
		context->exit_status = NORMAL_ERROR;
		perror("minishell pwd");
		return ;
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	context->exit_status = NORMAL_EXIT;
}
