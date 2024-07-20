#include "../../include/minishell.h"

void	lexer(t_context *ctx, char *line)
{
	t_token	*token;
	t_token	*token_head;

	token = token_init(ctx);
	token_head = token;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(*line))
			operator(&line, line, token);
		else if (is_quote(*line))
			quote(&line, line, token);
		else if (is_word(*line))
			word(&line, line, token);
		else
			tokenize_error("Unexpected Token", &line, line);
		token = token->next;
	}
	token_node_add(token, token_node_create("", TK_EOF, GENERAL)); // EOFの時のデータはNULLで合ってるか
	printf("\n----------- lexer start-------------\n");
	print_lexer(token_head);
	printf("----------- lexer end --------------\n\n");
}

	// expansion(token_head); // typeがDOUBLE_QUOTEのときにexpansionする
// このループにexpansion入れるか、double_quote_removalのところでexpansionするか迷い中
