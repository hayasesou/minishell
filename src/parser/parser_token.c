#include "minishell.h"

t_token *cat_token(t_token *token)
{
    t_token *new_token;
    t_token *tmp;

    new_token = token;
    tmp = token;
    while (token->next != NULL && is_string(token))
    {
        if (is_cat_token(token))
            join_tokens(&new_token, &tmp);
        else if (token->type == TK_WORD && token->next->type == TK_WORD)
            join_words(&new_token, &tmp);
        else
            break;
        tmp = tmp->next;
    }
    return (new_token);
}

// トークン結合:連続するトークンを結合するための関数
void join_tokens(t_token **new_token, t_token **tmp)
{
    char *joined_str;

    joined_str = ft_strjoin((*new_token)->data, (*tmp)->next->data);
    free((*new_token)->data);
    (*new_token)->data = joined_str;
}


void join_words(t_token **new_token, t_token **tmp)
{
    char *joined_str;

    joined_str = ft_strjoin((*tmp)->data, " ");
    free((*tmp)->data);
    (*tmp)->data = joined_str;
    *new_token = *tmp;
}

void init_cmd(t_parser **args, t_token *token)
{
    (*args)->cmd = malloc(sizeof(char *) * 2);
    if ((*args)->cmd == NULL)
        fatal_error("parser: append_token malloc error");
    (*args)->cmd[0] = strdup(token->data);
    (*args)->cmd[1] = NULL;
}

void append_token(t_parser **args, t_token *token)
{
    int i;
    char **new_cmd;

    if ((*args)->cmd == NULL)
    {
        init_cmd(args, token);
        return;
    }
    i = 0;
    while ((*args)->cmd[i] != NULL)
        i++;
    new_cmd = malloc(sizeof(char *) * (i + 2));
    if (new_cmd == NULL)
        fatal_error("parser: append_token malloc error");
    i = 0;
    while ((*args)->cmd[i] != NULL)
    {
        new_cmd[i] = (*args)->cmd[i];
        i++;
    }
    new_cmd[i] = strdup(token->data);
    new_cmd[i + 1] = NULL;
    free((*args)->cmd);
    (*args)->cmd = new_cmd;
}

void    arg_node_create(t_parser **args, t_token *token)
{
    t_parser *node;

    // トークンが文字列の場合、コマンドに追加
    if (is_string(token))
    {
        node = *args;
        while (node->cmd != NULL)
            node = node->next;
        append_token(args, token);
    }
    else if (is_redirect(token))
        file_node_add(*args, token->data, get_redirect_type(token->type)); // リダイレクトノードの追加
    else if (is_pipe(token))
        parser_pipe(args); // パイプの処理
    else
        err_exit(token->data, "parser: arg_node_add invalid token type", 0);
}
