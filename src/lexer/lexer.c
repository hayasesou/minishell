
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
			tokenize_error("Unexpected Token", &line, line);
	}
	token->next = add_token(NULL, TK_EOF, GENERAL);
	return (head->next);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		free(tmp);
	}
}

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
	ctx->env_head = env_head;
	ctx->exit_status = 0;
	return (ctx);
}

