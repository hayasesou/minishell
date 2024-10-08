#include "minishell.h"

void lexer_exec(t_token *token, char *line, bool space_before)
{
    while (*line && is_blank(*line))
        line++;
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
}

void lexer(t_context *ctx, char *line)
{
    t_token *token;
    t_token *token_head;
    bool space_before;

    token = token_init(ctx);
    token_head = token;
    space_before = false;
    lexer_exec(ctx->token_head, line, space_before);
    token_node_add(token, token_node_create("", TK_EOF));
    expansion(token_head,  ctx);
//    printf("\n----------- lexer start-------------\n");
//    print_lexer(token_head);
//    printf("----------- lexer end --------------\n\n");
}
