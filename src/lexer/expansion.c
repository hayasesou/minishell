#include "minishell.h"

// 変数展開
void    expand_variables(t_context *ctx, t_token *token)
{
    char    *expanded;
    char    *var_start; // $の位置
    char    *var_end; // 変数の終わり
    char    *var_name;
    char    *var_value;

    expanded = ft_strdup(token->data);
    while ((var_start = ft_strchr(expanded, '$')) != NULL)
    {
        var_end = var_start + 1;
        while (ft_isalnum(*var_end) || *var_end == '_')
            var_end++;
        var_name = strndup(var_start + 1, var_end - var_start - 1);
        // var_value = get_env_value();　// 環境変数の値を取得
    }
}

void    expansion(t_context *ctx, t_token *token)
{
    t_token *token_tmp;

    token_tmp = token;
    while (token_tmp != NULL)
    {
        if (token_tmp->type == TK_DOUBLE_QUOTE || token_tmp->type == TK_SPACE_DOUBLE_QUOTE)
        {
            expand_variables(ctx, token_tmp);
        }
        token_tmp = token_tmp->next;
    }
}