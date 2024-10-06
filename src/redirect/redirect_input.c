#include "minishell.h"

//if you use env which is not defined in redirect input,
//bash will display "ambiguous redirect"
//e.g)
//cat < $undefined_env
//bash: $undeifned_env: ambiguous redirect
//before redireting, our bash  will do expantion and
//if it is not defined in env, it will make "\0" string 
int	redirect_input(t_file *file, t_context *context, int *status)
{
	int	fd;

	if (file->filename[0] == '\0')
	{
		context->exit_status = 1;
		unexisted_env_error(file->filename);
		*status = 1;
		return (0);
	}
	fd = open(file->filename, O_RDONLY);
	if (fd == -1)
	{
		context->exit_status = 1;
		error_message(file->filename);
		*status = 1;
		return (0);
	}
	context->exit_status = 0;
	return (fd);
}




bool	is_input(t_file *file)
{
	if (file == NULL)
		return (false);
	return (file->type == IN_FILE
		|| file->type == HEREDOC || file->type == QUOTE_HEREDOC);
}
