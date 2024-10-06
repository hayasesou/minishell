#include "minishell.h"

void	error_handling_heredoc_newline(t_context *context, int *heredoc_status)
{
	context->exit_status = 1;
	*heredoc_status = 1;
	fatal_error("malloc error");
}

static	char	*heredoc_join(char *brefore_env,
	char *env_value, char *after_env, size_t *current_index)
{
	char	*new_line;
	char	*tmp;
	size_t	next_index;

	next_index = ft_strlen(brefore_env) + ft_strlen(env_value);
	tmp = ft_strjoin(brefore_env, env_value);
	free(brefore_env);
	free(env_value);
	if (tmp == NULL)
	{
		free(after_env);
		return (NULL);
	}
	new_line = ft_strjoin(tmp, after_env);
	free(tmp);
	free(after_env);
	if (new_line == NULL)
		return (NULL);
	*current_index = next_index;
	return (new_line);
}

static	void	make_env_name(t_expantion_info *info,
	size_t *i, t_context *context, int *heredoc_status)
{
	size_t	j;

	j = 0;
	info->before_env = ft_substr(info->line, 0, *i -1);
	if (info->before_env == NULL)
		error_handling_heredoc_newline(context, heredoc_status);
	while (ft_isalnum(info->line[*i + j]) || info->line[*i + j] == '_')
		j++;
	info->after_env = ft_substr(
			info->line, *i + j, ft_strlen(info->line) - (*i + j));
	if (info->after_env == NULL)
	{
		free(info->before_env);
		error_handling_heredoc_newline(context, heredoc_status);
	}
	info->env_name = ft_substr(info->line, *i, j);
	if (info->env_name == NULL)
	{
		free(info->before_env);
		free(info->after_env);
		error_handling_heredoc_newline(context, heredoc_status);
	}
}

char	*make_heredoc_newline(char *line,
	size_t *i, t_context *context, int *heredoc_status)
{
	char				*env_value;
	t_expantion_info	info;

	info.line = line;
	make_env_name(&info, i, context, heredoc_status);
	env_value = ft_strdup(
			heredoc_get_env_value(info.env_name,
				context->env_head, context, heredoc_status));
	if (env_value == NULL)
	{
		free(info.before_env);
		free(info.after_env);
		free(info.env_name);
		error_handling_heredoc_newline(context, heredoc_status);
	}
	free(info.env_name);
	if (env_value == NULL)
		env_value = ft_strdup("");
	return (heredoc_join(info.before_env, env_value, info.after_env, i));
}
