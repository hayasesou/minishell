/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayase <hayase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:12:17 by hayase            #+#    #+#             */
/*   Updated: 2024/10/18 23:12:44 by hayase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_file_redirect(t_file *file,
	t_context *context, int *redirect_status, t_tmp_fd *tmp_fd)
{
	if (is_output(file))
		output_process(file, context, redirect_status, &tmp_fd->tmp_output_fd);
	else if (is_input(file))
	{
		if (tmp_fd->tmp_input_fd != -1)
			close_fd(tmp_fd->tmp_input_fd, context);
	}
	else
		exception_process(context, redirect_status);
}

void	builtin_redirect(t_parser *parser,
	t_context *context, int *redirect_status)
{
	int			stdin_backup_fd;
	int			stdout_backup_fd;
	t_file		*file;
	t_tmp_fd	tmp_fd;

	tmp_fd.tmp_input_fd = -1;
	tmp_fd.tmp_output_fd = -1;
	stdin_backup_fd = backup_fd(STDIN_FILENO);
	stdout_backup_fd = backup_fd(STDOUT_FILENO);
	file = parser->file;
	while (file)
	{
		handle_file_redirect(file, context, redirect_status, &tmp_fd);
		file = file->next;
	}
	if (tmp_fd.tmp_output_fd != -1)
		dup2_fd(tmp_fd.tmp_output_fd, STDOUT_FILENO, context);
	if (tmp_fd.tmp_input_fd != -1)
		dup2_fd(tmp_fd.tmp_input_fd, STDIN_FILENO, context);
	exec_minishell_builtin(parser, context, parser->cmd[0]);
	restore_fd(stdin_backup_fd, STDIN_FILENO);
	restore_fd(stdout_backup_fd, STDOUT_FILENO);
}
