/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:19:54 by hayase            #+#    #+#             */
/*   Updated: 2024/10/18 23:52:18 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

t_context	*minishell_init(int ac, char **av, char **envp)
{
	t_context	*ctx;
	t_env		*env_head;

	(void)ac;
	(void)av;
	env_head = env_init(envp);
	if (env_head == NULL)
		return (NULL);
	ctx = (t_context *)malloc(sizeof(t_context));
	if (ctx == NULL)
	{
		free_env(env_head);
		return (NULL);
	}
	ctx->env_head = env_head;
	ctx->exit_status = 0;
	ctx->token_head = NULL;
	ctx->parser_head = NULL;
	ctx->sys_error = false;
	return (ctx);
}

bool	check_pipe(t_parser *parser)
{
	if (parser->next == NULL)
		return (false);
	return (true);
}

void	main_exec(char *line, t_context *ctx)
{
	ctx->sys_error = false;
	if (g_signal == 1 || g_signal == SIGINT)
		ctx->exit_status = 1;
	g_signal = 0;
	lexer(ctx, line);
	if (ctx->token_head == NULL)
	{
		free(line);
		return ;
	}
	parser(ctx);
	free_token(&ctx->token_head);
	ctx->token_head = NULL;
	if (ctx->parser_head == NULL)
		return ;
	if (check_pipe(ctx->parser_head))
		minishell_pipe(ctx->parser_head, ctx);
	else
		minishell_no_pipe(ctx->parser_head, ctx);
	free_parser(&ctx->parser_head);
	ctx->parser_head = NULL;
	free(line);
}

void	main_loop(t_context *ctx, char *line)
{
	while (1)
	{
		signal_init(ctx);
		line = readline("\033[1;33mminishell$\033[0m ");
		if (line == NULL)
			break ;
		if (strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		main_exec(line, ctx);
		delete_tmpfile();
	}
}

int	main(int ac, char **av, char **envp)
{
	int			status;
	char		*line;
	t_context	*ctx;

	rl_outstream = stderr;
	status = 0;
	ctx = minishell_init(ac, av, envp);
	if (ctx == NULL)
		return (1);
	line = NULL;
	main_loop(ctx, line);
	free_all(ctx);
	return (status);
}
