#include "../../include/minishell.h"

//gcc lexer.c token.c -lreadline

t_token	*token_node_create(char *data, t_token_type type, t_token_state state)
{
	t_token	*new_token;

	if (data == NULL && type != TK_EOF)
		return (NULL);
	new_token = (t_token *)calloc(1, sizeof(t_token));
	if (new_token == NULL)
		fatal_error("tokenize: add token calloc error");
	if (strlen(data) == 0)
		new_token->data = NULL;
	else
	{
		new_token->data = strdup(data);
		if (new_token->data == NULL)
			perror("tokenize: add token strdup error");
	}
	new_token->type = type;
	new_token->state = state;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	token_node_add(t_token *token, t_token *new_token)
{
	if (token == NULL || new_token == NULL)
		return ;
	new_token->prev = token;
	new_token->next = NULL;
	token->next = new_token;
}

t_token	*token_init(t_context *ctx)
{
	t_token	*head;

	head = calloc(1, sizeof(t_token));
	if (!head)
	{
		perror("calloc error in tokenize : token_init ");
		exit (1); // 後でちゃんとしたエラーに修正
	}
	head->data = NULL;
	head->type = TK_EMPTY;
	head->next = head;
	head->prev = head;
	ctx->token_head = head;
	return (head);
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