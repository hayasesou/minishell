/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:37:09 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:37:10 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_check(t_pipex *pipex, t_context *context, int *status, int cmd_num)
{
	if (pipe(pipex->pipe_fd[cmd_num]) == -1)
	{
		context->exit_status = -1;
		*status = -1;
		fatal_error("pipe error\n");
	}
}

int	fork_check(t_context *context, int *status)
{
	int	ret;

	ret = fork();
	if (ret == -1)
	{
		context->exit_status = -1;
		*status = -1;
		fatal_error("fork error\n");
	}
	return (ret);
}
