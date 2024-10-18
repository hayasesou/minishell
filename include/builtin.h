/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:09:10 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:30:31 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// builtin.c
void	exec_cmd(t_parser *parser, t_context *context);

// builtin_minishell.c
bool	is_minishell_builtin(char *cmd);
void	exec_minishell_builtin(t_parser *parser, t_context *context, char *cmd);

// builtin_bash.c
void	bash_builtin(t_parser *parser, t_context *context);

// builtin_cd.c
void	cd_builtin(t_parser *parser, t_context *context);

// builtin_pwd.c
void	pwd_builtin(t_context *context);

// builtin_export.c
void	export_builtin(t_parser *parser, t_context *context);

// builtin_export_utils.c
void	no_arg_export(t_env *env_head);
void	arg_export(t_env *env_head, char *arg, t_context *context);

// builtin_echo.c
void	echo_builtin(t_parser *parser, t_context *context);

// builtin_env.c
void	env_builtin(t_parser *parser, t_context *context);

// builtin_unset.c
void	unset_builtin(t_parser *parser, t_context *context);

#endif