/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:32 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 22:19:30 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

static char	**duplicate_commands(char **cmd, int count)
{
	char	**new_cmd;
	int		i;

	new_cmd = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_cmd[i] = ft_strdup(cmd[i]);
		if (!new_cmd[i])
		{
			while (--i >= 0)
				free(new_cmd[i]);
			free(new_cmd);
			return (NULL);
		}
		i++;
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}

int	add_command(t_parser *cur_arg, char *cmd_str)
{
	int		count;
	char	**new_cmd;

	count = 0;
	while (cur_arg->cmd && cur_arg->cmd[count])
		count++;
	new_cmd = duplicate_commands(cur_arg->cmd, count);
	if (!new_cmd)
		return (0);
	new_cmd[count] = ft_strdup(cmd_str);
	if (!new_cmd[count])
	{
		free_command(new_cmd);
		return (0);
	}
	new_cmd[count + 1] = NULL;
	free_command(cur_arg->cmd);
	cur_arg->cmd = new_cmd;
	return (1);
}

static char	*combine_words(t_token **token_tmp)
{
	char	*combined_str;
	char	*temp;

	combined_str = NULL;
	if (!*token_tmp)
		return (NULL);
	combined_str = ft_strdup((*token_tmp)->data);
	if (!combined_str)
		return (NULL);
	*token_tmp = (*token_tmp)->next;
	while (*token_tmp && is_not_space_string(*token_tmp))
	{
		temp = ft_strjoin(combined_str, (*token_tmp)->data);
		if (!temp)
		{
			free(combined_str);
			return (NULL);
		}
		free(combined_str);
		combined_str = temp;
		*token_tmp = (*token_tmp)->next;
	}
	return (combined_str);
}

static int	add_words_command(t_parser *cur_arg, t_token **token_tmp)
{
	char	*combined_str;

	combined_str = combine_words(token_tmp);
	if (!combined_str)
		return (0);
	if (!add_command(cur_arg, combined_str))
	{
		free(combined_str);
		return (0);
	}
	free(combined_str);
	return (1);
}

void	create_command(t_parser *args, t_token *token)
{
	t_token		*token_tmp;
	t_parser	*cur_arg;

	token_tmp = token;
	cur_arg = args;
	while (token_tmp && token_tmp->type != TK_EOF && token_tmp->type != TK_PIPE)
	{
		if (is_redirect(token_tmp))
		{
			if (!add_redirect(cur_arg, token_tmp))
				return ;
			token_tmp = token_tmp->next->next;
		}
		else if (is_string(token_tmp))
		{
			if (!add_words_command(cur_arg, &token_tmp))
				return ;
		}
		else
			token_tmp = token_tmp->next;
	}
}
