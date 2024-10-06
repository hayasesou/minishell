#include "minishell.h"

void	close_fd(int fd, t_context *context)
{
	if (close(fd) == -1)
	{
		context->exit_status = 1;
		fatal_error("close error");
	}
}


void	dup2_fd(int old_fd, int new_fd, t_context *context)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		context->exit_status = 1;
		fatal_error("dup2 error");
	}
	close_fd(old_fd, context);
}
