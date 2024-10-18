/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 03:57:36 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 04:01:11 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_variables(t_env *env_head)
{
	t_env	*env_tmp;
	int		count;

	count = 0;
	env_tmp = env_head->next;
	while (env_tmp != env_head)
	{
		count++;
		env_tmp = env_tmp->next;
	}
	return (count);
}

char	**allocate_env_list(int count)
{
	char	**env_list;

	env_list = (char **)malloc(sizeof(char *) * (count + 1));
	if (env_list == NULL)
		return (NULL);
	return (env_list);
}

int	populate_env_list(t_env *env_head, char **env_list, t_context *context)
{
	t_env	*env_tmp;
	int		i;

	env_tmp = env_head->next;
	i = 0;
	while (env_tmp != env_head)
	{
		env_list[i] = env_join(env_tmp->env_name, env_tmp->env_val, context);
		if (env_list[i] == NULL)
		{
			while (i > 0)
			{
				i--;
				free(env_list[i]);
			}
			free(env_list);
			context->exit_status = NORMAL_ERROR;
			return (0);
		}
		env_tmp = env_tmp->next;
		i++;
	}
	env_list[i] = NULL;
	return (1);
}

char	**make_env_list(t_env *env_head, t_context *context)
{
	int		count;
	char	**env_list;

	count = count_env_variables(env_head);
	env_list = allocate_env_list(count);
	if (env_list == NULL)
	{
		context->exit_status = NORMAL_ERROR;
		return (NULL);
	}
	if (!populate_env_list(env_head, env_list, context))
		return (NULL);
	return (env_list);
}

char	*get_env_value(char *env_name, t_env *env_head)
{
	t_env	*env_tmp;

	env_tmp = env_head->next;
	while (env_tmp != env_head)
	{
		if ((ft_strncmp(env_tmp->env_name, env_name, ft_strlen(env_name)) == 0)
			&& (env_tmp->env_name[ft_strlen(env_name)] == '\0'))
			return (ft_strdup(env_tmp->env_val));
		env_tmp = env_tmp->next;
	}
	return (NULL);
}
