/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:39:25 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 22:39:50 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
