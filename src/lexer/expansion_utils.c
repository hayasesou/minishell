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

char **ft_split_charset(char *s, char *charset)
{
    char    **result;
    size_t  words;
    size_t  i;
    char    *start;
    size_t  len;

    i = 0;
    if (!s || !charset)
        return (NULL);
    words = count_words(s, charset);
    result = (char **)malloc((words + 1) * sizeof(char *));
    if (!result)
        return (NULL);
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
        result[i] = ft_strndup(start, len);
        if (!result[i++])
        {
            while (i > 0)
                free(result[--i]);
            free(result);
            return (NULL);
        }
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

t_token *expansion_split(t_token *node)
{
    char **array;
    t_token *current_node;
    size_t i;
    bool preceded_by_space;

    // 元のノードがスペースで始まっているかどうかを判断
    preceded_by_space = (node->type == TK_SPACE_WORD || node->type == TK_SPACE_DOUBLE_QUOTE || node->type == TK_SPACE_SINGLE_QUOTE);

    i = 0;
    array = ft_split_charset(node->data, " \t");
    if (array == NULL)
        return (fatal_error("malloc error"), NULL);

    current_node = node;
    while (array[i] != NULL)
    {
        if (i == 0)
        {
            if (preceded_by_space)
                token_node_add(current_node, token_node_create(array[i], TK_SPACE_WORD));
            else
                token_node_add(current_node, token_node_create(array[i], TK_WORD));
        }
        else
        {
            token_node_add(current_node, token_node_create(array[i], TK_SPACE_WORD));
        }
        current_node = current_node->next;
        free(array[i]);
        i++;
    }
    free(array);

    // 元のノードを削除
    token_node_delete(node);
    return (current_node);
}
