/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayase <hayase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:32:12 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 05:52:52 by hayase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PROGRAM_NAME "./minishell"

static void	exec_command(t_parser *parser, t_context *context, char *cmd_path)
{
	char	*shell_level;
	char	**env_list;

	if (ft_strncmp(parser->cmd[0], PROGRAM_NAME, ft_strlen(PROGRAM_NAME)) == 0)
	{
		shell_level = get_env_value("SHLVL", context->env_head);
		set_env_value("SHLVL", ft_itoa(ft_atoi(shell_level) + 1),
			context->env_head, context);
		free(shell_level);
	}
	env_list = make_env_list(context->env_head, context);
	execve(cmd_path, parser->cmd, env_list);
	free(cmd_path);
	free_env_list(env_list);
	ft_printf("execve error\n");
	free_all_env_node(context->env_head);
	context->exit_status = NORMAL_ERROR;
	exit(NORMAL_ERROR);
}

static void	check_file_and_execute(t_parser *parser, t_context *context,
		char *cmd_path)
{
	if (access(cmd_path, F_OK) == 0 && cmd_path[ft_strlen(cmd_path) - 1] != '/')
	{
		if (access(cmd_path, X_OK) == 0)
			exec_command(parser, context, cmd_path);
		else
		{
			ft_printf("minishell : %s: Permission denied\n", parser->cmd[0]);
			free_all_env_node(context->env_head);
			context->exit_status = PERMISSION_DENIED;
			exit(PERMISSION_DENIED);
		}
	}
	return ;
}

// "path" + "/" + "cmd"
// e.g.) "/usr/bin" + "/" + "ls"
static char	*make_cmd_path(char *path, int start, int i, t_parser *parser)
{
	char	*stash_dir1;
	char	*stash_dir2;
	char	*cmd_path;

	if (i == start)
		i = ft_strlen(path);
	stash_dir1 = ft_substr(path, start, i - start);
	if (stash_dir1 == NULL)
		return (NULL);
	stash_dir2 = ft_strjoin(stash_dir1, "/");
	free(stash_dir1);
	if (stash_dir2 == NULL)
		return (NULL);
	cmd_path = ft_strjoin(stash_dir2, parser->cmd[0]);
	free(stash_dir2);
	if (cmd_path == NULL)
		return (NULL);
	return (cmd_path);
}

static bool	check_file_type(t_parser *parser, t_context *context, char **path)
{
	struct stat	st;

	*path = get_env_value("PATH", context->env_head);
	if (path == NULL)
	{
		context->exit_status = NORMAL_ERROR;
		ft_printf("PATH not found\n");
		exit(NORMAL_ERROR);
	}
	if (ft_strchr(parser->cmd[0], '/') != NULL)
	{
		if (stat(parser->cmd[0], &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				ft_printf("minishell : %s: Is a directory\n", parser->cmd[0]);
				context->exit_status = IS_DIR;
				exit(IS_DIR);
			}
			check_file_and_execute(parser, context, parser->cmd[0]);
		}
		return (true);
	}
	return (false);
}

// imginable input of t_parsaer->cmd[0]: ls or usr/bin/ls or usr/bin  or ./a.out
void	bash_builtin(t_parser *parser, t_context *context)
{
	char	*path;
	int		i;
	int		start;
	char	*cmd_path;

	initialize_value(&i, &start);
	if (check_file_type(parser, context, &path) == true)
	{
		free(path);
		return ;
	}
	if (path == NULL)
		return ;
	while (path[i] != '\0')
	{
		if (path[i] == ':' || ft_strchr(path, ':') == NULL)
		{
			cmd_path = make_cmd_path(path, start, i, parser);
			check_file_and_execute(parser, context, cmd_path);
			free(cmd_path);
			start = i + 1;
		}
		i++;
	}
	free(path);
}
