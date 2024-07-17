
#include "../include/struct.h"
#include "../include/lexer.h"

//gcc lexer.c token.c -lreadline

t_token	*token_init(void)
{
	t_token	*head;

	head = calloc(1, sizeof(t_token));
	if (!head)
	{
		perror("calloc error in tokenize : token_init ");
		exit (1); // 後でちゃんとしたエラーに修正
	}
	head->data = NULL;
	head->type = NULL;
	head->state = GENERAL;
	head->next = head;
	head->prev = head;
	return (head);
}

t_token	*tokenize(char *line)
{
	t_token	*head;
	t_token	*token;

	head = token_init();
	token = head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line))
		{
			token = token->next;
			token = operator(&line, line);
		}
		else if (is_word(line))
		{
			token = token->next;
			token = word(&line, line);
		}
		else
			printf("tokenize: unexpected token");
		//	assert_error("tokenize: unexpected token");
	}
	token->next = add_token(NULL, TK_EOF, GENERAL);
	return (head->next);
}

void	free_tokens(t_token *token)
{
	t_token *tmp;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		free(tmp);
	}
}

//int	main(void)
//{
//	char	*line;
//	t_token	*tokens;

//	rl_outstream = stderr;
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (line == NULL)
//			break ;
//		if (*line)
//		{
//			tokens = tokenize(line);
//			// トークン処理のデバッグ出力
//			for (t_token *token = tokens; token; token = token->next)
//			{
//				printf("Token type: %d, data: %s\n", token->type, token->data);
//			}
//			free_tokens(tokens);
//		}
//		free(line);
//	}
//	exit(0);
//}

t_env	*node_new_set(t_env *env_node, char *str)
{
	// dupする部分調べる
	env_node->env_name = strdup(str);
	if (env_node->env_name == NULL)
		return (NULL);
	env_node->env_val = strdup(str);
	if (env_node->env_val == NULL)
		return (NULL);
	return (env_node);
}

t_env	*node_new(char *str)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (env_node == NULL)
		return (NULL);
	if (strlen(str) == 0)
	{
		env_node->env_name = NULL;
		env_node->env_val = NULL;
	}
	else
	{
		env_node = node_new_set(env_node, str);
		if (env_node == NULL)
			return (NULL);
	}
	env_node->next = NULL;
	env_node->prev = NULL;
	return (env_node);
}

t_env	*env_head_init(void)
{
	t_env	*head;

	head = node_new("");
	if (head == NULL)
		return (NULL);
	head->next = head;
	head->prev = head;
	return (head);
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*new;
	int		i;

	i = 0;
	head = env_head_init();
	while (envp[i])
	{
		new = node_new(envp[i]);
		if (new == NULL)
		{
			// free_env_all
			return (NULL);
		}
		node_add(head, new);
		i++;
	}
	return (head);
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
	ctx->env = env_head;
	ctx->status = 0;
	return (ctx);
}

int	main(int ac, char **av, char **envp)
{
	int		status;
	char	*line;

	rl_outstream = stderr;
	status = 0;
	minishell_init(ac, av, envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			tokenize(line);
		}
		status = interpret(line);
		free(line);
	}
	exit(status);
}
