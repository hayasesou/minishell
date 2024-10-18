/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:09:04 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:30:22 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "builtin.h"
# include "error.h"
# include "ft_printf.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "redirect.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 1
# define LAST_CMD_PID 0
# define SPECIFIED_DIR 1
# define NORMAL_EXIT 0
# define NORMAL_ERROR 1
# define SYNTAX_ERROR 258
# define COMMAND_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define IS_DIR 126

extern int	g_signal;

// error
void		syntax_error(char *msg, t_context *ctx);
void		fatal_error(char *msg);

// env
t_env		*node_new_set(t_env *env_node, char *str);
t_env		*node_new(char *str);
void		node_add(t_env *head, t_env *new);
t_env		*env_head_init(void);
t_env		*env_init(char **envp);

// env_utils.c
char		**make_env_list(t_env *env_head, t_context *context);
void		free_env_list(char **env_list);
void		free_all_env_node(t_env *env_head);
char		*get_env_value(char *env_name, t_env *env_head);
char		*heredoc_get_env_value(char *env_name, t_env *env_head,
				t_context *context, int *heredoc_status);
void		set_env_value(char *env_name, char *new_env_value, t_env *env_head,
				t_context *context);
char		*find_first_equal(char *str);
char		*ft_strndup(char *str, size_t n);

// signal
void		signal_init(t_context *ctx);
void		set_signal_handler(void);
void		set_signal_parent_handler(void);
void		set_signal_child_handler(void);
void		set_heredoc_signal_parent_handler(void);
void		set_heredoc_signal_child_handler(void);
void		signal_handler(int signum);
void		signal_parent_handler(int signum);
void		heredoc_signal_parent_handler(int signum);

// free
void		free_token(t_token **head);
void		free_file(t_file *head);
void		free_parser(t_parser **head);
void		free_env_node(t_env *node);
void		free_env(t_env *head);
void		free_all(t_context *ctx);

// main
void		main_loop(t_context *ctx, char *line);
t_context	*minishell_init(int ac, char **av, char **envp);
void		signal_init(t_context *ctx);
int			exec(char argv[]);
void		validate_access(const char *path, const char *filename);
char		*search_path(const char *filename);

#endif
