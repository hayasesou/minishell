/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:37:23 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:37:24 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static void	child_process(t_parser *tmp_parser, t_pipex *pipe_x,
		t_context *context, int *status)
{
	if (tmp_parser->prev != NULL)
		prev_pipe(pipe_x, pipe_x->current_cmd_num);
	if (tmp_parser->next != NULL)
		next_pipe(pipe_x, pipe_x->current_cmd_num);
	redirect(tmp_parser, context, status);
	setup_heredoc_fd(tmp_parser);
	exec_cmd(tmp_parser, context);
}

static void	wait_child_and_close_pipe(t_parser *parser, t_pipex *pipe_x)
{
	int	i;

	i = 0;
	while (i < pipe_x->current_cmd_num)
	{
		waitpid(pipe_x->pids[i], NULL, 0);
		i++;
	}
	dup2(pipe_x->stdin_fd, STDIN_FILENO);
	dup2(pipe_x->stdout_fd, STDOUT_FILENO);
	close(pipe_x->stdin_fd);
	close(pipe_x->stdout_fd);
	free_pipex(parser, pipe_x);
}

// Implementation of the minishell_pipe function
void	minishell_pipe(t_parser *parser_head, t_context *context)
{
	t_pipex		pipe_x;
	t_parser	*tmp_parser;
	int			status;

	tmp_parser = parser_head;
	status = SUCCESS;
	init_pipex(tmp_parser, &pipe_x, context, &status);
	process_heredoc(tmp_parser, context, &status);
	while (tmp_parser != NULL)
	{
		set_heredoc_signal_parent_handler();
		if (tmp_parser->next != NULL)
			pipe_check(&pipe_x, context, &status, pipe_x.current_cmd_num);
		pipe_x.pids[pipe_x.current_cmd_num] = fork_check(context, &status);
		pipe_x.last_cmd_pid = pipe_x.pids[pipe_x.current_cmd_num];
		if (pipe_x.pids[pipe_x.current_cmd_num] == 0)
		{
			set_signal_child_handler();
			child_process(tmp_parser, &pipe_x, context, &status);
		}
		if (pipe_x.current_cmd_num > 0)
			close_pipe_fd(&pipe_x);
		close_heredoc_fds(tmp_parser);
		pipe_x.current_cmd_num++;
		tmp_parser = tmp_parser->next;
	}
	wait_child_and_close_pipe(parser_head, &pipe_x);
	set_signal_handler();
}
