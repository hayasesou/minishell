#include "minishell.h"

// void	lexer(t_context *ctx, char *line)
// {
// 	t_token	*token;
// 	t_token	*token_head;

// 	token = token_init(ctx);
// 	token_head = token;
// 	while (*line)
// 	{
// 		if (consume_blank(&line, line))
// 			continue ;
// 		else if (is_operator(*line))
// 			operator(&line, line, token);
// 		else if (is_quote(*line))
// 			quote(&line, line, token);
// 		else if (is_word(*line))
// 			word(&line, line, token);
// 		else
// 			tokenize_error("Unexpected Token", &line, line);
// 		if (token->next)
// 			token = token->next;
// 	}
// 	token_node_add(token, token_node_create("", TK_EOF));
// 	printf("\n----------- lexer start-------------\n");
// 	print_lexer(token_head);
// 	printf("----------- lexer end --------------\n\n");
// }

	// expansion(token_head); // typeがDOUBLE_QUOTEのときにexpansionする
// このループにexpansion入れるか、double_quote_removalのところでexpansionするか迷い中

void lexer(t_context *ctx, char *line)
{
    t_token *token;
    t_token *token_head;
    int token_count = 0;

    token = token_init(ctx);
    token_head = token;
    while (*line)
    {
        if (consume_blank(&line, line))
            continue;
        else if (is_operator(*line))
        {
            operator(&line, line, token);
            printf("Debug: Operator token created. Data: [%s], Type: %d\n", token->next->data, token->next->type);
        }
        else if (is_quote(*line))
        {
            quote(&line, line, token);
            printf("Debug: Quote token created. Data: [%s], Type: %d\n", token->next->data, token->next->type);
        }
        else if (is_word(*line))
        {
            word(&line, line, token);
            printf("Debug: Word token created. Data: [%s], Type: %d\n", token->next->data, token->next->type);
        }
        else
            tokenize_error("Unexpected Token", &line, line);
        
        if (token->next)
        {
            token = token->next;
            token_count++;
        }
        printf("Debug: Current token count: %d\n", token_count);
    }
    token_node_add(token, token_node_create("", TK_EOF));
    printf("Debug: EOF token added. Total tokens: %d\n", token_count + 1);

    printf("\n----------- lexer start-------------\n");
    print_lexer(token_head);
    printf("----------- lexer end --------------\n\n");
}