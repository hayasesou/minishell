#include "minishell.h"

// 文字列内の$を展開する関数（ダブルクオーテーション内）
static void expand_string(t_token *token, t_context *ctx)
{
    size_t  i;

    i = 0;
    while (token->data[i])
    {
        if (token->data[i] == '$')
        {
            if (!is_env_name_char(token->data[i + 1]) &&
                token->data[i + 1] != '$' && token->data[i + 1] != '?')
                i++;
            else if (!is_heredoc_expansion(token))
                expansion_env(token->data, token, &i, ctx);
            else
                break ;
        }
        else
            i++;
    }
}

// 文字列内の$を展開する関数（クオーテーション外）
static void expand_value(t_token *token, t_context *ctx)
{
    size_t  i;
    t_token *new_token;

    i = 0;
    while (token->data[i])
    {
        if (token->data[i] == '$')
        {
            if (!is_env_name_char(token->data[i + 1]) &&
                token->data[i + 1] != '$' && token->data[i + 1] != '?')
                i++;
            else if (!is_heredoc_expansion(token))
                expansion_env(token->data, token, &i, ctx);
            else
                break ;
        }
        else
            i++;
    }
    if (ft_strchr(token->data, ' ') || ft_strchr(token->data, '\t'))
    {
        new_token = expansion_split(token);
        if (!new_token)
            fatal_error("Expansion: expansion_split failed");
    }
}

void expansion(t_token *token_head, t_context *ctx)
{
    t_token *tmp_token;

    tmp_token = token_head->next;
    while (tmp_token != NULL && tmp_token->type != TK_EOF)
    {
        if (is_double_quote_expansion(tmp_token->type))
            expand_string(tmp_token, ctx);
        else if (is_word_expansion(tmp_token->type))
            expand_value(tmp_token, ctx);
        tmp_token = tmp_token->next;
    }
}
