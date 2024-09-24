#include "minishell.h"

void token_node_delete(t_token *node)
{
    if (!node)
        return;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    if (node->data)
        free(node->data);
    free(node);
}

static char **split_token_data(t_token *node, bool *preceded_by_space)
{
    char    **array;

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
    size_t          i;
    t_token_type    type;
    t_token         *new_token;

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
    char       **array;
    t_token    *prev_node;
    bool       preceded_by_space;

    array = split_token_data(node, &preceded_by_space);
    prev_node = node->prev;
    token_node_delete(node);
    prev_node = create_tokens_from_array(array, preceded_by_space, prev_node);
    free(array);
    return prev_node;
}
