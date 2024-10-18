#include "minishell.h"

void	output_process(t_file *file,
	t_context *context, int *redirect_status, int *tmp_output_fd)
{
	if (*tmp_output_fd != -1)
		close_fd(*tmp_output_fd, context);
	if (file->type == OUT_FILE)
		*tmp_output_fd = redirect_output(file, context, redirect_status);
	else if (file->type == APPEND)
		*tmp_output_fd = append_output(file, context, redirect_status);
}

void	input_process(t_file *file,
	t_context *context, int *redirect_status, int *tmp_input_fd)
{
	if (*tmp_input_fd != -1)
		close_fd(*tmp_input_fd, context);
	if (file->type == IN_FILE)
		*tmp_input_fd = redirect_input(file, context, redirect_status);
	else if (file->type == HEREDOC)
		*tmp_input_fd = file->heredoc_fd;
	else if (file->type == QUOTE_HEREDOC)
		*tmp_input_fd = file->heredoc_fd;
}

void	exception_process(t_context *context, int *redirect_status)
{
	context->exit_status = 1;
	*redirect_status = 1;
	fatal_error("redirect error");
}

void	redirect(t_parser *parser, t_context *context, int *redirect_status)
{
	int		tmp_input_fd;
	int		tmp_output_fd;
	t_file	*file;

	file = parser->file;
	tmp_input_fd = -1;
	tmp_output_fd = -1;
	while (file != NULL)
	{
		if (is_output(file))
			output_process(file, context, redirect_status, &tmp_output_fd);
		else if (is_input(file))
			input_process(file, context, redirect_status, &tmp_input_fd);
		else
			exception_process(context, redirect_status);
		file = file->next;
	}
	if (tmp_output_fd != -1)
		dup2_fd(tmp_output_fd, STDOUT_FILENO, context);
	if (tmp_input_fd != -1)
		dup2_fd(tmp_input_fd, STDIN_FILENO, context);
}

void	builtin_redirect(t_parser *parser,
	t_context *context, int *redirect_status)
{
	int		tmp_input_fd;
	int		tmp_output_fd;
	t_file	*file;
	int		stdin_backup_fd;
	int		stdout_backup_fd;

	stdin_backup_fd = backup_fd(STDIN_FILENO);
	stdout_backup_fd = backup_fd(STDOUT_FILENO);
	file = parser->file;
	tmp_input_fd = -1;
	tmp_output_fd = -1;
	while (file != NULL)
	{
		if (is_output(file))
			output_process(file, context, redirect_status, &tmp_output_fd);
		else if (is_input(file))
		{
			if (tmp_input_fd != -1)
				close_fd(tmp_input_fd, context);
		}
		else
			exception_process(context, redirect_status);
		file = file->next;
	}
	if (tmp_output_fd != -1)
		dup2_fd(tmp_output_fd, STDOUT_FILENO, context);
	if (tmp_input_fd != -1)
		dup2_fd(tmp_input_fd, STDIN_FILENO, context);
	exec_minishell_builtin(parser, context, parser->cmd[0]);
	restore_fd(stdin_backup_fd, STDIN_FILENO);
	restore_fd(stdout_backup_fd, STDOUT_FILENO);
}
