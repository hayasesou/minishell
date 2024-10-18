/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayase <hayase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:30:49 by hayase            #+#    #+#             */
/*   Updated: 2024/10/18 23:34:14 by hayase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_parser(t_parser **head_ref)
// {
// 	t_parser	*tmp;
// 	t_parser	*delete;
// 	int			i;

// 	if (*head_ref == NULL)
// 		return ;
// 	tmp = *head_ref;
// 	while (tmp != NULL)
// 	{
// 		i = 0;
// 		if (tmp->cmd != NULL)
// 		{
// 			while (tmp->cmd[i] != NULL)
// 				free(tmp->cmd[i++]);
// 			free(tmp->cmd);
// 			tmp->cmd = NULL;
// 		}
// 		if (tmp->file != NULL)
// 		{
// 			free_file(tmp->file);
// 			tmp->file = NULL;
// 		}
// 		delete = tmp;
// 		tmp = tmp->next;
// 		free(delete);
// 	}
// 	*head_ref = NULL;
// }
void	free_cmd(char **cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_parser_node(t_parser *node)
{
	if (node->cmd != NULL)
	{
		free_cmd(node->cmd);
		node->cmd = NULL;
	}
	if (node->file != NULL)
	{
		free_file(node->file);
		node->file = NULL;
	}
	free(node);
}

void	free_parser(t_parser **head_ref)
{
	t_parser	*tmp;
	t_parser	*delete;

	if (*head_ref == NULL)
		return ;
	tmp = *head_ref;
	while (tmp != NULL)
	{
		delete = tmp;
		tmp = tmp->next;
		free_parser_node(delete);
	}
	*head_ref = NULL;
}
