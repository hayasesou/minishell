
#include "../include/struct.h"
#include "../include/lexer.h"

//gcc lexer.c token.c -lreadline

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

void	*tokenize(t_context *ctx, char *line)
{
	t_token	*head;
	t_token	*token;

	head = token_init(ctx);
	if (ctx->token_head == NULL)
	{
		free(line);
		return (NULL);
	}
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



