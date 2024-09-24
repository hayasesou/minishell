#include "minishell.h"

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
		return (NULL);
	ctx->env_head = env_head;
	ctx->exit_status = 0;
	return (ctx);
}


void minishell_no_pipe(t_parser *parser, t_context *context)
{
	int status;
	int pid;
	
	if(parser->cmd == NULL)
		return ;
	if(is_minishell_builtin(parser->cmd[0]))
	{
		process_heredoc(parser, context, &status);
		redirect(parser, context, &status);
		setup_heredoc_fd(parser);
		// exec_cmd(parser, context);
		exec_minishell_builtin(parser, context, parser->cmd[0]);
	}
	else
	{
		pid = fork();
		if(pid == 0)
		{
			process_heredoc(parser, context, &status);
			redirect(parser, context, &status);
			setup_heredoc_fd(parser);
			exec_cmd(parser, context);
		}
		else
		{
		waitpid(pid, &status, 0);
		context->exit_status = WEXITSTATUS(status);
		}
	}
}


bool check_pipe(t_parser *parser)
{
	if(parser->next == NULL)
		return (false);
	return (true);
}

void	main_loop(t_context *ctx, char *line)
{
	t_parser	*parsed;

	while (1)
	{
		line = readline("\033[1;33mminishell$\033[0m ");
		if (line == NULL)
			break ;
		if (strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		if (*line)
		{
			add_history(line);
			lexer(ctx, line);
			parsed = parser(ctx);
			// print_parser(parsed);
			if(check_pipe(parsed))
				minishell_pipe(parsed, ctx);
			else
				minishell_no_pipe(parsed, ctx);
			// print_parser(parsed);
			delete_tmpfile();
		}
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		status;
	char	*line;
	t_context	*ctx;

	rl_outstream = stderr;
	status = 0;
	ctx = minishell_init(ac, av, envp);
	if (ctx == NULL)
		return (1);
	line = NULL;
	main_loop(ctx, line);
	exit(status);
}
