#include "minishell.h"

/* 判定関数 */

bool is_env_name(char c)
{
    return (ft_isalnum(c) || c == '_');
}

bool is_heredoc_expansion(t_token *token)
{
    return (token->prev && token->prev->type == TK_REDIR_HEREDOC);
}

bool is_env_name_start(char c)
{
    return (ft_isalpha(c) || c == '_');
}

bool is_env_name_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

/* 文字列連結関数 */

char *ft_strjoin_all(char *s1, char *s2, char *s3)
{
    char *temp;
    char *result;

    temp = ft_strjoin(s1, s2);
    if (!temp)
        return (NULL);
    result = ft_strjoin(temp, s3);
    free(temp);
    return (result);
}

/* 特殊な環境変数を取得する関数 */

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

/* 環境変数名の値を取得する関数 */

static char *get_env_variable_value(char *data, size_t *i, t_context *ctx)
{
    char *env_name;
    char *env_value;
    size_t var_len;

    var_len = 0;
    (*i)++;

    while (data[*i + var_len] && is_env_name_char(data[*i + var_len]))
        var_len++;

    env_name = ft_substr(data, *i, var_len);
    if (!env_name)
        fatal_error("Expansion: ft_substr failed");

    env_value = get_env_value(env_name, ctx->env_head);
    if (!env_value)
        env_value = ft_strdup("");
    else
        env_value = ft_strdup(env_value);

    if (!env_value)
        fatal_error("Expansion: ft_strdup failed");

    free(env_name);
    *i += var_len;

    return env_value;
}

/* 環境変数の値を取得するメイン関数 */

static char *get_env_value_from_data(char *data, size_t *i, t_context *ctx)
{
    char *env_value;

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

/* トークンデータを再構築する関数 */

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

/* 環境変数の展開を行う関数 */

static void expansion_env(char *data, t_token *token, size_t *i, t_context *ctx)
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

/* 文字列内の$を展開する関数（ダブルクオーテーション内） */

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

/* 文字列内の$を展開する関数（クオーテーション外） */

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

/* トークンタイプの判定関数 */

bool is_double_quote_expansion(t_token_type type)
{
    return (type == TK_DOUBLE_QUOTE || type == TK_SPACE_DOUBLE_QUOTE);
}

bool is_word_expansion(t_token_type type)
{
    return (type == TK_WORD || type == TK_SPACE_WORD);
}

/* トークンリスト全体に対する展開処理 */

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
