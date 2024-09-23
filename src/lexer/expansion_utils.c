#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
    char	*joined;

    if (!s1 || !s2)
        return (NULL);
    joined = ft_strjoin(s1, s2);
    if (!joined)
        return (NULL);
    free(s1);
    return (joined);
}

static bool is_charset(char c, const char *charset)
{
    while (*charset)
    {
        if (c == *charset)
            return (true);
        charset++;
    }
    return (false);
}

static size_t count_words(const char *s, const char *charset)
{
    size_t count;
    bool in_word;

    count = 0;
    in_word = false;
    while (*s)
    {
        if (is_charset(*s, charset))
            in_word = false;
        else if (!in_word)
        {
            in_word = true;
            count++;
        }
        s++;
    }
    return count;
}

static char **allocate_result(size_t words)
{
    char **result;

    result = (char **)malloc((words + 1) * sizeof(char *));
    return (result);
}

static void free_result(char **result, size_t i)
{
    while (i > 0)
    {
        free(result[--i]);
    }
    free(result);
}

static int copy_word(char **result, char *start, size_t len, size_t *i)
{
    result[*i] = ft_strndup(start, len);
    if (!result[*i])
        return (0);
    (*i)++;
    return (1);
}

static int split_loop(char **result, char *s, char *charset, size_t *i)
{
    char    *start;
    size_t  len;

    while (*s)
    {
        if (is_charset(*s, charset))
        {
            s++;
            continue;
        }
        start = s;
        len = 0;
        while (*s && !is_charset(*s, charset))
        {
            s++;
            len++;
        }
        if (!copy_word(result, start, len, i))
            return (0);
    }
    return (1);
}

char **ft_split_charset(char *s, char *charset)
{
    char    **result;
    size_t  words;
    size_t  i;

    if (!s || !charset)
        return (NULL);
    i = 0;
    words = count_words(s, charset);
    result = allocate_result(words);
    if (!result)
        return (NULL);
    if (!split_loop(result, s, charset, &i))
    {
        free_result(result, i);
        return (NULL);
    }
    result[i] = NULL;
    return (result);
}

void token_node_delete(t_token *node)
{
    if (!node)
        return;

    // 前後のノードをリンク
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    // ノードのデータを解放
    if (node->data)
        free(node->data);

    // ノード自体を解放
    free(node);
}

static char **split_token_data(t_token *node, bool *preceded_by_space)
{
    char **array;

    *preceded_by_space = (node->type == TK_SPACE_WORD ||
                          node->type == TK_SPACE_DOUBLE_QUOTE ||
                          node->type == TK_SPACE_SINGLE_QUOTE);
    array = ft_split_charset(node->data, " \t");
    if (array == NULL)
        fatal_error("Expansion: ft_split_charset failed");
    return array;
}

static t_token *create_tokens_from_array(char **array, bool preceded_by_space, t_token *prev_node)
{
    size_t i;
    t_token_type type;
    t_token *new_token;

    i = 0;
    while (array[i])
    {
        if (i == 0)
            type = preceded_by_space ? TK_SPACE_WORD : TK_WORD;
        else
            type = TK_SPACE_WORD;
        new_token = token_node_create(array[i], type);
        if (!new_token)
            fatal_error("Expansion: token_node_create failed");
        token_node_add(prev_node, new_token);
        prev_node = new_token;
        free(array[i]);
        i++;
    }
    return prev_node;
}

t_token *expansion_split(t_token *node)
{
    char **array;
    t_token *prev_node;
    bool preceded_by_space;

    array = split_token_data(node, &preceded_by_space);
    prev_node = node->prev;
    token_node_delete(node);
    prev_node = create_tokens_from_array(array, preceded_by_space, prev_node);
    free(array);
    return prev_node;
}
