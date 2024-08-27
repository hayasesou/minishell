#include "minishell.h"

void lexer(t_context *ctx, char *line)
{
    t_token *token;
    // t_token *token_head;
    bool space_before = false;

    token = token_init(ctx);
    // token_head = token;
    while (*line)
    {
        if (is_blank(*line))
        {
            space_before = true;
            line++;
            continue;
        }
        else if (is_operator(*line))
        {
            operator(&line, line, token);
            space_before = false;
        }
        else if (is_quote(*line))
        {
            quote(&line, line, token, space_before);
            space_before = false;
        }
        else if (is_word(*line))
        {
            word(&line, line, token, space_before);
            space_before = false;
        }
        else
            tokenize_error("Unexpected Token", &line, line);
        if (token->next)
            token = token->next;
    }
    token_node_add(token, token_node_create("", TK_EOF));
    // printf("\n----------- lexer start-------------\n");
    // print_lexer(token_head);
    // printf("----------- lexer end --------------\n\n");
}

// TODO:expansion(token_head); // typeがDOUBLE_QUOTEのときにexpansionする
