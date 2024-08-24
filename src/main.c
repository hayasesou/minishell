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

void	main_loop(t_context *ctx, char *line)
{
	t_parser	*parsed;

	while (1)
	{
		line = readline("minishell$ ");
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
			print_parser(parsed);
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
