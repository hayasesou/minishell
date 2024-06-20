#include "../../include/lexer.h"

t_token	*add_token(t_token_type type, t_token *cur, char *data)
{
	t_token	*token;

	token = calloc(1, sizeof(t_token));
	if (!token)
	{
		perror("calloc error in tokenize");
		exit(1); // 後でちゃんとしたエラーに修正
	}
	token->type = type;
	token->data = strdup(data);
	if (!token->data)
	{
		perror("strdup error in tokenize");
		exit(1); // 後でちゃんとしたエラーに修正
	}
	cur->next = token;
	token->prev = cur;
	return (token);
}
