#include "minishell.h"

// $$, $?など特殊な環境変数を取得する関数
static char *get_special_env_value(char *data, size_t *i, t_context *ctx)
{
    char *env_value;

    if (data[*i + 1] == '$')
    {
        env_value = ft_itoa(getpid());
        if (!env_value)
            fatal_error("Expansion: ft_itoa failed");
        *i += 2;
    }
    else if (data[*i + 1] == '?')
    {
        env_value = ft_itoa(ctx->exit_status);
        if (!env_value)
            fatal_error("Expansion: ft_itoa failed");
        *i += 2;
    }
    else
    {
        env_value = ft_strdup("$");
        if (!env_value)
            fatal_error("Expansion: ft_strdup failed");
        (*i)++;
    }
    return env_value;
}

// 環境変数名の値を取得する関数
static char *get_env_variable_value(char *data, size_t *i, t_context *ctx)
{
    char    *env_name;
    char    *env_value;
    size_t  var_len;
    size_t  start;

    start = *i; // '$' の位置を記録
    var_len = 0;
    (*i)++; // '$' を消費
    while (data[*i + var_len] && is_env_name_char(data[*i + var_len]))
        var_len++;
    env_name = ft_substr(data, *i, var_len);
    if (!env_name)
        fatal_error("Expansion: ft_substr failed");
    env_value = get_env_value(env_name, ctx->env_head);
    if (!env_value) // 環境変数が見つからない場合、元の文字列を返す
        env_value = ft_substr(data, start, var_len + 1); // '+1' は '$' の分
    else
        env_value = ft_strdup(env_value);
    if (!env_value)
        fatal_error("Expansion: ft_substr failed");
    free(env_name);
    *i += var_len;
    return env_value;
}

// 環境変数の値を取得するメイン関数
static char *get_env_value_from_data(char *data, size_t *i, t_context *ctx)
{
    char    *env_value;

    if (data[*i] != '$')
    {
        (*i)++;
        return NULL;
    }
    if (data[*i + 1] == '$' || data[*i + 1] == '?')
        env_value = get_special_env_value(data, i, ctx);
    else if (is_env_name_start(data[*i + 1]))
        env_value = get_env_variable_value(data, i, ctx);
    else
    {
        env_value = ft_strdup("$");
        if (!env_value)
            fatal_error("Expansion: ft_strdup failed");
        (*i)++;
    }
    return env_value;
}

// トークンデータを再構築する関数
static char *rebuild_token_data(char *data, size_t start, char *env_value, size_t *i)
{
    char    *before;
    char    *after;
    char    *new_data;

    before = ft_substr(data, 0, start);
    if (!before)
        fatal_error("Expansion: ft_substr before failed");
    after = ft_strdup(&data[*i]);
    if (!after)
    {
        free(before);
        fatal_error("Expansion: ft_strdup after failed");
    }
    new_data = ft_strjoin_all(before, env_value, after);
    if (!new_data)
    {
        free(before);
        free(after);
        fatal_error("Expansion: ft_strjoin_all failed");
    }
    free(before);
    free(after);
    return (new_data);
}

// 環境変数の展開を行う関数
void expansion_env(char *data, t_token *token, size_t *i, t_context *ctx)
{
    size_t  start;
    char    *env_value;
    char    *new_data;

    start = *i;
    env_value = get_env_value_from_data(data, i, ctx);
    if (!env_value)
    {
        (*i)++;
        return;
    }
    new_data = rebuild_token_data(data, start, env_value, i);
    if (!new_data)
        fatal_error("Expansion: rebuild_token_data failed");
    free(token->data);
    token->data = new_data;
    *i = start + ft_strlen(env_value);
    free(env_value);
}
