/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:18:38 by hayase            #+#    #+#             */
/*   Updated: 2024/10/19 01:19:31 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_no_pipe_process(t_parser *parser, t_context *context, int *status)
{
	set_signal_child_handler();
	process_heredoc(parser, context, status);
	redirect(parser, context, status);
	setup_heredoc_fd(parser);
	exec_cmd(parser, context, true);
}

void	minishell_no_pipe(t_parser *parser, t_context *context)
{
	int	status;
	int	pid;

	if (parser->cmd == NULL)
		return ;
	if (is_minishell_builtin(parser->cmd[0]))
	{
		process_heredoc(parser, context, &status);
		builtin_redirect(parser, context, &status);
	}
	else
	{
		set_signal_parent_handler();
		pid = fork();
		if (pid == 0)
		{
			child_no_pipe_process(parser, context, &status);
		}
		else
		{
			waitpid(pid, &status, 0);
			context->exit_status = WEXITSTATUS(status);
			set_signal_handler();
		}
	}
}
