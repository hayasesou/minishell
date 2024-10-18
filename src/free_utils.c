/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:54:50 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 01:54:51 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(char **cmd)
{
	size_t	i;

	i = 0;
	if (cmd == NULL)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void	free_env_node(t_env *node)
{
	if (node == NULL)
		return ;
	free(node->env_name);
	node->env_name = NULL;
	free(node->env_val);
	node->env_val = NULL;
	free(node);
	node = NULL;
}

void	free_env(t_env *head)
{
	t_env	*cur;
	t_env	*next;

	cur = head->next;
	if (head == NULL)
		return ;
	while (cur != head)
	{
		next = cur->next;
		free_env_node(cur);
		cur = next;
	}
	free_env_node(head);
}
