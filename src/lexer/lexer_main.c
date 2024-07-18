
#include "../include/struct.h"
#include "../include/lexer.h"

//gcc lexer.c token.c -lreadline

t_token	*token_node_create(char *data, t_token_type type, t_token_state state)
{
	t_token	*new_token;

	if (data == NULL)
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
	// set_token_type(new_token);
	new_token->type = type;
	new_token->state = state;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	token_node_add(t_token *head, t_token *new_token)
{
	if (head == NULL || new_token == NULL)
		return ;
	new_token->next = head;
	new_token->prev = head->prev;
	head->prev->next = new_token;
	head->prev = new_token;
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
	head->type = NULL;
	head->state = GENERAL;
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

void	*lexer(t_context *ctx, char *line)
{
	t_token	*token;

	token = token_init(ctx);
	if (ctx->token_head == NULL)
	{
		free(line);
		return (NULL);
	}
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
	token_node_add(token, token_node_create(NULL, TK_EOF, GENERAL)); // EOFの時のデータはNULLで合ってるか
}
