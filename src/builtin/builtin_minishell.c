/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:35:49 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 01:53:00 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_minishell_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0
		&& (ft_strlen(cmd) == ft_strlen("echo")))
		return (true);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0
		&& (ft_strlen(cmd) == ft_strlen("cd")))
		return (true);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0
		&& (ft_strlen(cmd) == ft_strlen("pwd")))
		return (true);
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0
		&& (ft_strlen(cmd) == ft_strlen("export")))
		return (true);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0
		&& (ft_strlen(cmd) == ft_strlen("unset")))
		return (true);
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0
		&& (ft_strlen(cmd) == ft_strlen("env")))
		return (true);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0
		&& (ft_strlen(cmd) == ft_strlen("exit")))
		return (true);
	return (false);
}

void	exec_minishell_builtin(t_parser *parser, t_context *context, char *cmd,
		bool is_parent)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0
		&& (ft_strlen(cmd) == ft_strlen("echo")))
		echo_builtin(parser, context);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0
		&& (ft_strlen(cmd) == ft_strlen("cd")))
		cd_builtin(parser, context);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0
		&& (ft_strlen(cmd) == ft_strlen("pwd")))
		pwd_builtin(context);
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0
		&& (ft_strlen(cmd) == ft_strlen("export")))
		export_builtin(parser, context);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0
		&& (ft_strlen(cmd) == ft_strlen("unset")))
		unset_builtin(parser, context);
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0
		&& (ft_strlen(cmd) == ft_strlen("env")))
		env_builtin(parser, context);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0
		&& (ft_strlen(cmd) == ft_strlen("exit")))
		exit_builtin(parser, context, is_parent);
}
