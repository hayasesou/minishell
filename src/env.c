/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:39:38 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 03:47:02 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*node_new_set(t_env *env_node, char *str)
{
	char	*equal_pos;
	size_t	env_name_len;

	equal_pos = find_first_equal(str);
	if (equal_pos == NULL)
	{
		env_node->env_name = ft_strdup(str);
		if (env_node->env_name == NULL)
			return (NULL);
		env_node->env_val = NULL;
		return (env_node);
	}
	env_name_len = (equal_pos - str) / sizeof(char);
	env_node->env_name = ft_strndup(str, env_name_len);
	if (env_node->env_name == NULL)
		return (NULL);
	env_node->env_val = ft_strdup(equal_pos + 1);
	if (env_node->env_val == NULL)
	{
		free(env_node->env_name);
		return (NULL);
	}
	return (env_node);
}

t_env	*node_new(char *str)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (env_node == NULL)
		return (NULL);
	if (ft_strlen(str) == 0)
	{
		env_node->env_name = NULL;
		env_node->env_val = NULL;
	}
	else
	{
		env_node = node_new_set(env_node, str);
		if (env_node == NULL)
		{
			free(env_node);
			return (NULL);
		}
	}
	env_node->next = NULL;
	env_node->prev = NULL;
	return (env_node);
}

t_env	*env_head_init(void)
{
	t_env	*head;

	head = node_new("");
	if (head == NULL)
		return (NULL);
	head->next = head;
	head->prev = head;
	return (head);
}

void	node_add(t_env *head, t_env *new)
{
	if (head == NULL || new == NULL)
		return ;
	new->next = head;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*new;
	int		i;

	i = 0;
	head = env_head_init();
	if (head == NULL)
		return (NULL);
	while (envp[i])
	{
		new = node_new(envp[i]);
		if (new == NULL)
		{
			free_env(head);
			return (NULL);
		}
		node_add(head, new);
		i++;
	}
	return (head);
}
