#include "minishell.h"

char *ft_strjoin(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char *result = (char *)malloc(len1 + len2 + 1);

    if (result == NULL) {
        fprintf(stderr, "メモリの割り当てに失敗しました。\n");
        return NULL;
    }
    strcpy(result, str1);
    strcat(result, str2);

    return result;
}

void join_words(char **combined_str, t_token **tmp)
{
    char *joined_str;

    joined_str = ft_strjoin(*combined_str, (*tmp)->data);
    free((*tmp)->data);
    *combined_str = joined_str;
}

t_redirect_type get_redirect_type(t_token_type type)
{
    switch (type)
    {
        case TK_REDIR_IN:
            return IN_FILE;
        case TK_REDIR_OUT:
            return OUT_FILE;
        case TK_REDIR_APPEND:
            return APPEND;
        case TK_REDIR_HEREDOC:
            return HEREDOC;
        default:
            return UNKNOWN;
    }
}
