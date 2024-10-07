#include "minishell.h"

static	int	heredoc_readline(char **line,
	t_heredoc *heredoc, t_context *context, int *heredoc_status)
{
	char	*new_line;

	*line = readline(">");
	if (*line == NULL)
		return (1);
	if (ft_strncmp(*line, heredoc->deliminater,
			ft_strlen(*line)) == 0
		&& ft_strlen(*line) == ft_strlen(heredoc->deliminater))
	{
		free(*line);
		return (1);
	}
	new_line = heredoc_expantion(*line, context, heredoc_status);
	if (new_line == NULL)
	{
		context->exit_status = 1;
		return (1);
	}
	write(heredoc->tmpfile_fd, new_line, ft_strlen(new_line));
	write(heredoc->tmpfile_fd, "\n", 1);
	free(new_line);
	return (0);
}

int	heredoc(t_file *file, t_context *context, int *heredoc_status)
{
	t_heredoc	heredoc;
	char		*line;

	heredoc.deliminater = file->filename;
	create_tmpfile(&heredoc, context, heredoc_status);
	while (1)
	{
		if (heredoc_readline(&line, &heredoc, context, heredoc_status) == 1)
			break ;
	}
	close(heredoc.tmpfile_fd);
	heredoc.tmpfile_fd = open(heredoc.tmpfile, O_RDONLY);
	free(heredoc.tmpfile);
	return (heredoc.tmpfile_fd);
}

static	int	quote_heredoc_readline(char **line,
	t_heredoc *heredoc, t_context *context, int *heredoc_status)
{
	char	*new_line;

	*line = readline(">");
	if (*line == NULL)
		return (1);
	if (ft_strncmp(*line, heredoc->deliminater,
			ft_strlen(*line)) == 0
		&& ft_strlen(*line) == ft_strlen(heredoc->deliminater))
	{
		free(*line);
		return (1);
	}
	new_line = ft_strjoin(*line, "\n");
	free(*line);
	if (new_line == NULL)
	{
		context->exit_status = 1;
		*heredoc_status = 1;
		return (1);
	}
	write(heredoc->tmpfile_fd, new_line, ft_strlen(new_line));
	free(new_line);
	return (0);
}

int	quote_heredoc(t_file *file, t_context *context, int *heredoc_status)
{
	t_heredoc	heredoc;
	char		*line;

	heredoc.deliminater = file->filename;
	create_tmpfile(&heredoc, context, heredoc_status);
	while (1)
	{
		if (quote_heredoc_readline(&line,
				&heredoc, context, heredoc_status) == 1)
			break ;
	}
	close(heredoc.tmpfile_fd);
	heredoc.tmpfile_fd = open(heredoc.tmpfile, O_RDONLY);
	free(heredoc.tmpfile);
	return (heredoc.tmpfile_fd);
}
