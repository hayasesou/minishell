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
