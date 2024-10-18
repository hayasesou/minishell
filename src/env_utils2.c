/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 03:16:23 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 03:19:59 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_first_equal(char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == '=')
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strndup(char *str, size_t n)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (n + 1));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str, n + 1);
	return (new_str);
}

void	free_env_list(char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i] != NULL)
	{
		free(env_list[i]);
		i++;
	}
	free(env_list);
}

void	free_all_env_node(t_env *env_head)
{
	t_env	*env_tmp;
	t_env	*env_tmp2;

	env_tmp = env_head->next;
	while (env_tmp != env_head)
	{
		free(env_tmp->env_name);
		free(env_tmp->env_val);
		env_tmp2 = env_tmp;
		env_tmp = env_tmp->next;
		free(env_tmp2);
	}
	free(env_head);
}
