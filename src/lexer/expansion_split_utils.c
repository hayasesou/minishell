#include "minishell.h"

static char **allocate_result(size_t words)
{
    char    **result;

    result = (char **)malloc((words + 1) * sizeof(char *));
    return (result);
}

static size_t count_words(const char *s, const char *charset)
{
    size_t  count;
    bool    in_word;

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
