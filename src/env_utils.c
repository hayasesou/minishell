/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:39:36 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 04:00:14 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_join(char *env_name, char *env_value, t_context *context)
{
	char	*tmp_str;
	char	*env_str;

	tmp_str = ft_strjoin(env_name, "=");
	if (tmp_str == NULL)
	{
		context->exit_status = NORMAL_ERROR;
		return (NULL);
	}
	env_str = ft_strjoin(tmp_str, env_value);
	free(tmp_str);
	return (env_str);
}

int	set_env_value_loop(t_context *context, t_env *env_head, char *env_name,
		char *new_env_value)
{
	t_env	*env_tmp;

	env_tmp = env_head->next;
	while (env_tmp != env_head)
	{
		if ((ft_strncmp(env_tmp->env_name, env_name, ft_strlen(env_name)) == 0)
			&& (env_tmp->env_name[ft_strlen(env_name)] == '\0'))
		{
			free(env_tmp->env_val);
			env_tmp->env_val = ft_strdup(new_env_value);
			if (env_tmp->env_val == NULL)
			{
				context->exit_status = NORMAL_ERROR;
				perror("minishell setenv");
				return (0);
			}
			return (1);
		}
		env_tmp = env_tmp->next;
	}
	return (0);
}

void	set_env_value(char *env_name, char *new_env_value, t_env *env_head,
		t_context *context)
{
	t_env	*new_env_node;

	if (!set_env_value_loop(context, env_head, env_name, new_env_value))
	{
		new_env_node = node_new(env_name);
		if (new_env_node == NULL)
		{
			context->exit_status = NORMAL_ERROR;
			return ;
		}
		new_env_node->env_val = ft_strdup(new_env_value);
		if (new_env_node->env_val == NULL)
		{
			free(new_env_node);
			context->exit_status = NORMAL_ERROR;
			return ;
		}
		node_add(env_head, new_env_node);
	}
}
