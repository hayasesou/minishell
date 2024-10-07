#include "minishell.h"

//confirm the existence of the file in the current directory
static	bool	check_file_existence(char *file_name)
{
	if (access(file_name, F_OK) == -1)
		return (false);
	return (true);
}

static	bool	create_tmpfile_name(char **tmpfile,
	t_context *context, int *heredoc_status, int i)
{
	char	*tmp_num;

	tmp_num = ft_itoa(i);
	if (tmp_num == NULL)
	{
		context->exit_status = 1;
		*heredoc_status = 1;
		fatal_error("malloc error");
	}
	*tmpfile = ft_strjoin(HEREDOCTMP, tmp_num);
	free(tmp_num);
	if (*tmpfile == NULL)
	{
		context->exit_status = 1;
		*heredoc_status = 1;
		fatal_error("malloc error");
	}
	if (check_file_existence(*tmpfile) == false)
		return (true);
	return (false);
}

void	create_tmpfile(t_heredoc *heredoc,
	t_context *context, int *heredoc_status)
{
	int		fd;
	char	*tmpfile;
	int		i;

	i = 0;
	while (1)
	{
		if (create_tmpfile_name(&tmpfile, context, heredoc_status, i) == true)
			break ;
		i++;
	}
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		context->exit_status = 1;
		*heredoc_status = 1;
		error_message("tmpfile");
		free(tmpfile);
	}
	heredoc->tmpfile = tmpfile;
	heredoc->tmpfile_fd = fd;
}

void	delete_tmpfile(void)
{
	char	*tmp_num;
	char	*tmpfile;
	int		i;

	i = 0;
	tmp_num = ft_itoa(i);
	tmpfile = ft_strjoin(HEREDOCTMP, tmp_num);
	free(tmp_num);
	while (access(tmpfile, F_OK) != -1)
	{
		unlink(tmpfile);
		free(tmpfile);
		i++;
		tmp_num = ft_itoa(i);
		tmpfile = ft_strjoin(HEREDOCTMP, tmp_num);
		free(tmp_num);
		if (tmpfile == NULL)
			fatal_error("malloc error");
	}
	free(tmpfile);
}
