#include "../include/minishell.h"

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = getenv("PATH");
	while (*value)
	{
		bzero(path, PATH_MAX);
		end = strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			strlcpy(path, value, PATH_MAX);
		strlcat(path, "/", PATH_MAX);
		strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			dup = strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

int	exec(char argv[])
{
	extern char	**environ;
	const char	*path;
	pid_t		pid;
	int			wstatus;

	path = &argv[0];
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		if (strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, &argv[0]);
		// rxecve(path, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

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

// int	interpret(t_context *ctx, char *line)
// {
// 	t_token	*token;
// 	char	**argv;

// 	token = tokenize(line);
// 	if (token->type == TK_EOF)
// 		;
// 	else if (syntax_error)
// 		ctx->exit_status = ERROR_TOKENIZE;
// 	else
// 	{
// 		expand(token);
// 		argv = token_list_to_argv(token);
// 		ctx->exit_status = exec(argv);
// 		free_argv(argv);
// 	}
// 	free(token);
// }

void	main_loop(t_context *ctx, char *line)
{
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
			// perser(ctx, line);
		}
		// ctx->exit_status = interpret(ctx, line); // interpretはtokenizeと被ってる
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
