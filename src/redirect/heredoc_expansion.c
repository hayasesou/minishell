/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:36:57 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:36:58 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_get_env_value(char *env_name,
	t_env *env_head, t_context *context, int *heredoc_status)
{
	char	*env_value;
	t_env	*tmp_env;

	if (env_head == NULL)
		return (NULL);
	tmp_env = env_head->next;
	while (tmp_env != env_head)
	{
		if (ft_strncmp(env_name, tmp_env->env_name, ft_strlen(env_name)) == 0
			&& ft_strlen(env_name) == ft_strlen(tmp_env->env_name))
		{
			env_value = ft_strdup(tmp_env->env_val);
			if (env_value == NULL)
			{
				context->exit_status = 1;
				*heredoc_status = 1;
				fatal_error("malloc error");
			}
			return (env_value);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

static	void	error_handling(char *new_line,
	t_context *context, int *heredoc_status)
{
	if (new_line == NULL)
	{
		context->exit_status = 1;
		*heredoc_status = 1;
		fatal_error("malloc error");
	}
}

char	*heredoc_expantion(char *line, t_context *context, int *heredoc_status)
{
	size_t	i;
	char	*new_line;

	i = 0;
	new_line = ft_strdup(line);
	error_handling(new_line, context, heredoc_status);
	free(line);
	while (new_line[i] != '\0')
	{
		if (new_line[i++] == '$')
		{
			if (new_line[i] == '\0')
				break ;
			else if (new_line[i] == '$')
				continue ;
			else
			{
				new_line = make_heredoc_newline(new_line,
						&i, context, heredoc_status);
				if (new_line == NULL)
					return (NULL);
			}
		}
	}
	return (new_line);
}
