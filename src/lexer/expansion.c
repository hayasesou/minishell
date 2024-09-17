#include "minishell.h"

// 環境変数名を取得する関数
static char *get_var_name(char *str, int *len)
{
    int i;

    i = 0;
    if (*str == '{')
    {
        str++;
        while (str[i] && str[i] != '}')
            i++;
        if (str[i] == '}')
        {
            *len = i + 1; // '{' と '}' を含む長さ
            return (ft_strndup(str, i));
        }
        else
        {
            *len = i;
            return (ft_strndup(str, i));
        }
    }
    else
    {
        while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
            i++;
        *len = i;
        return (ft_strndup(str, i));
    }
}

// 環境変数を展開し、結果を返す関数
static char *replace_var(char *str, t_env *env_head, t_context *ctx, int *i)
{
    char    *var_name;
    char    *var_value;
    char    *temp;
    int     len;

    if (str[*i + 1] == '$')
    {
        temp = ft_itoa(getpid());
        if (!temp)
            fatal_error("Expansion: itoa failed");
        (*i) += 2;
        return (temp);
    }
    if (str[*i + 1] == '?')
    {
        temp = ft_itoa(ctx->exit_status);
        if (!temp)
            fatal_error("Expansion: itoa failed");
        (*i) += 2;
        return (temp);
    }
    var_name = get_var_name(&str[*i + 1], &len);
    if (var_name == NULL)
    {
        *i += 1;
        return (ft_strdup("$"));
    }
    var_value = get_env_value(var_name, env_head);
    if (var_value == NULL)
        var_value = ft_strdup("");
    *i += len + 1;
    free(var_name);
    return (var_value);
}

// 文字列内の$を展開する関数
static char *expand_string(char *str, t_env *env_head, t_context *ctx)
{
    char    *result;
    char    *temp;
    int     i;
    int     j;

    result = ft_strdup("");
    if (!result)
        fatal_error("Expansion: strdup failed");
    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            temp = replace_var(str, env_head, ctx, &i);
            if (!temp)
                fatal_error("Expansion: replace_var failed");
            char *new_result = ft_strjoin_free(result, temp);
            if (!new_result)
            {
                free(result);
                fatal_error("Expansion: ft_strjoin_free failed");
            }
            result = new_result;
        }
        else
        {
            j = i;
            while (str[j] && str[j] != '$')
                j++;
            temp = ft_strndup(&str[i], j - i);
            if (!temp)
                fatal_error("Expansion: strndup failed");
            char *new_result = ft_strjoin_free(result, temp);
            if (!new_result)
            {
                free(result);
                free(temp);
                fatal_error("Expansion: ft_strjoin_free failed");
            }
            result = new_result;
            free(temp);
            i = j;
        }
    }
    return (result);
}
// expansion.c 内の expansion 関数修正

void expansion(t_token *token_head, t_env *env_head, t_context *ctx)
{
    t_token *current;
    char    *expanded;
    t_token *split_node;

    current = token_head->next;
    while (current != NULL && current->type != TK_EOF)
    {
        // シングルクォート内では展開を行わない
        if (current->type == TK_DOUBLE_QUOTE || current->type == TK_SPACE_DOUBLE_QUOTE || current->type == TK_WORD || current->type == TK_SPACE_WORD)
        {
            expanded = expand_string(current->data, env_head, ctx);
            if (!expanded)
                fatal_error("Expansion: expand_string failed");
            free(current->data);
            current->data = expanded;

            // 展開後にスペースやタブが含まれている場合はトークンを分割
            if (strchr(expanded, ' ') || strchr(expanded, '\t'))
            {
                split_node = expansion_split(current);
                if (split_node == NULL)
                    fatal_error("Expansion: split failed");
                current = split_node;
            }
        }
        current = current->next;
    }
}
