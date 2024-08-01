#include "minishell.h"

// トークン結合:連続するトークンを結合するための関数
t_token    *cat_token(t_token *token)
{
    t_token *new_token;
    t_token *tmp;
    char    *joined_str;

    new_token = token;
    tmp = token;
    while (token->next != TK_EOF && is_string(token))
    {
        if (is_cat_token(token))
        {
            joined_str = strjoin(new_token->data, tmp->next->data);
            free(new_token->data);
            new_token->data = joined_str;
        }
        else if (token->type == TK_WORD && token->next->type == TK_WORD)
        {
            joined_str = strjoin(token->data, " ");
            free(tmp->data);
            tmp->data = joined_str;
            new_token = tmp;
        }
        else
            break ;
        tmp = tmp->next;
    }
    return (new_token);
}

// コマンドノードの追加
t_parser    *args_init(void)
{
    t_parser    *args;

    args = (t_parser *)malloc(sizeof(t_parser));
    if (args == NULL)
        fatal_error("parser: args init malloc error");
    args->cmd = NULL;
    args->file = NULL;
    args->next = NULL;
    args->prev = NULL;
    return (args);
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
        append_token(args, token); // append_tokenは未定義？追加処理を実装
    }
    else if (is_redirect(token))
        file_node_add(*args, token); // リダイレクトノードの追加
    else if (is_pipe(token))
        parser_pipe(args); // パイプの処理
    else
        err_exit(token, "parser: arg_node_add invalid token type", 0);
}

// ファイルリダイレクトノードを追加する
void    file_node_add(char *filename, int type)
{
    t_file *file;
    t_file *cur;

    file = malloc(sizeof(t_file));
    if (!file)
        fatal_error("parser: file_node_add malloc error");

    file->filename = strdup(token->data);
    file->type = get_redirect_type(token->type); // リダイレクトタイプの取得
    file->next = NULL;

    if (args->file == NULL)
        args->file = file;
    else
    {
        cur = args->file;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = file;
    }
}

// コマンドを解析しノードを作成する
void    create_command(t_parser *args, t_token *token)
{
    t_token *tmp;
    t_parser *cur_arg;

    tmp = token;
    cur_arg = args;
    while (tmp->type != TK_EOF && tmp->type != TK_PIPE)
    {
        if (is_redirect(tmp))
            file_node_add(current_arg, tmp);
        else
            current_arg = arg_node_add(current_arg, tmp);
        tmp = tmp->next;
    }
}

void    command_init(t_parser *args)
{
    args->cmd = malloc(sizeof(char *) * 2);
    if (args->cmd == NULL)
        return (fatal_error("parser: command init malloc error"));
}

// パイプの処理
void    parser_pipe(t_parser **args)
{
    t_parser *next_arg;

    next_arg = args_init();
    if (next_arg == NULL)
        fatal_error("parser: parser_pipe malloc error");
    (*args)->next = next_arg;
    next_arg->prev = *args;
    *args = next_arg;
}*

void    parser(t_context *ctx)
{
    t_parser    *args;
    t_parser    *args_head;
    t_token     *token;

    args = args_init();
    if (args == NULL)
        fatal_error("parser: parser is NULL"); // 合ってる？
    args_head = args;
    token = ctx->token_head->next; // token head用のtoken_type作成するかTK_EMPTYのままにするかあとで考える
    command_init(args);
    while (token->type != TK_EOF)
    {
        create_command(args, token);
        if (token->type == TK_PIPE)
            parser_pipe(&args);
        token = token->next;
    }
    create_command(args, token);
    print_parser(parser_head);
    free_parser(args_head);
}
