/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_struct_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:37:14 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:37:15 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_process(t_parser *parser_head)
{
	t_parser	*tmp_parser;
	int			count;

	count = 0;
	tmp_parser = parser_head;
	while (tmp_parser != NULL)
	{
		count++;
		tmp_parser = tmp_parser->next;
	}
	return (count);
}

static	void	malloc_for_process(t_pipex *pipe_x,
	int count, t_context *context, int *heredoc_status)
{
	pipe_x->pids = (pid_t *)malloc(sizeof(pid_t) * count);
	if (pipe_x->pids == NULL)
	{
		context->exit_status = 1;
		*heredoc_status = 1;
		fatal_error("malloc error\n");
	}
}

static	void	malloc_for_pipe_fd(t_pipex *pipe_x,
	int count, t_context *context, int *heredoc_status)
{
	int	i;

	pipe_x->pipe_fd = (int **)malloc(sizeof(int *) * (count - 1));
	if (pipe_x->pipe_fd == NULL)
	{
		context->exit_status = 1;
		*heredoc_status = 1;
		free(pipe_x->pids);
		fatal_error("malloc error\n");
	}
	i = 0;
	while (i < count - 1)
	{
		pipe_x->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe_x->pipe_fd[i] == NULL)
		{
			while (i-- > 0)
				free(pipe_x->pipe_fd[i]);
			free_single_pipe_fd(pipe_x);
			context->exit_status = 1;
			*heredoc_status = 1;
			fatal_error("malloc error\n");
		}
		i++;
	}
}

static	void	stash_stdin_stdout(t_pipex *pipe_x,
	t_parser *parser_head, t_context *context, int *heredoc_status)
{
	pipe_x->stdin_fd = dup(STDIN_FILENO);
	if (pipe_x->stdin_fd == -1)
	{
		free_pipex(parser_head, pipe_x);
		context->exit_status = 1;
		*heredoc_status = 1;
		fatal_error("dup error\n");
	}
	pipe_x->stdout_fd = dup(STDOUT_FILENO);
	if (pipe_x->stdout_fd == -1)
	{
		free_pipex(parser_head, pipe_x);
		context->exit_status = 1;
		*heredoc_status = 1;
		fatal_error("dup error\n");
	}
}

//initialize pipex struct
// cmd1 | cmd2 | cmd3
//process count is 3
//pipe_fd count is 2
void	init_pipex(t_parser *parser_head,
	t_pipex *pipe_x, t_context *context, int *heredoc_status)
{
	int	count;

	count = count_process(parser_head);
	malloc_for_process(pipe_x, count, context, heredoc_status);
	malloc_for_pipe_fd(pipe_x, count, context, heredoc_status);
	stash_stdin_stdout(pipe_x, parser_head, context, heredoc_status);
	pipe_x->last_cmd_pid = LAST_CMD_PID;
	pipe_x->current_cmd_num = 0;
}
