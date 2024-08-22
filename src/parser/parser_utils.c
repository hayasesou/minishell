#include "minishell.h"

t_parser *arg_node_add(t_parser *args)
{
    t_parser *new_node = args_init();
    t_parser *last_node = args;

    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }
    last_node->next = new_node;
    new_node->prev = last_node;

    return new_node;
}

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
