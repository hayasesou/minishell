#include "../../include/minishell.h"
#include "../../include/lexer.h"
#include "../../include/struct.h"

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
		if (is_blank(*line))
			consume_blank(&line, line);
		else if (is_operator(*line))
		{
			operator(&line, line);
			token = token->next;
		}
		else if (is_word(*line))
		{
			word(&line, line);
			token = token->next;
		}
		else
			tokenize_error("Unexpected Token", &line, line);
	}
	token_node_add(token, token_node_create(NULL, TK_EOF, GENERAL)); // EOFの時のデータはNULLで合ってるか
}
