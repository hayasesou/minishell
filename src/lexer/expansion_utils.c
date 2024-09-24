#include "minishell.h"

void free_result(char **result, size_t i)
{
    while (i > 0)
        free(result[--i]);
    free(result);
}

char *ft_strjoin_all(char *s1, char *s2, char *s3)
{
    char    *tmp;
    char    *result;

    tmp = ft_strjoin(s1, s2);
    if (!tmp)
        return (NULL);
    result = ft_strjoin(tmp, s3);
    free(tmp);
    return (result);
}

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
