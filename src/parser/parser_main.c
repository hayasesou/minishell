#include "minishell.h"

// トークン結合:連続するトークンを結合するための関数
t_token    *cat_token(t_token *token)
{
    t_token *new_token;
    t_token *tmp;
    char    *joined_str;

    new_token = token;
    tmp = token;
    while (token->next->type != TK_EOF && is_string(token))
    {
        if (is_cat_token(token))
        {
            joined_str = ft_strjoin(new_token->data, tmp->next->data);
            free(new_token->data);
            new_token->data = joined_str;
        }
        else if (token->type == TK_WORD && token->next->type == TK_WORD)
        {
            joined_str = ft_strjoin(token->data, " ");
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

void append_token(t_parser **args, t_token *token)
{
    int i;
    char **new_cmd;

    if ((*args)->cmd == NULL) {
        (*args)->cmd = malloc(sizeof(char *) * 2);
        if ((*args)->cmd == NULL)
            fatal_error("parser: append_token malloc error");

        (*args)->cmd[0] = strdup(token->data);
        (*args)->cmd[1] = NULL;
        return;
    }

    for (i = 0; (*args)->cmd[i] != NULL; i++);

    new_cmd = malloc(sizeof(char *) * (i + 2));
    if (new_cmd == NULL)
        fatal_error("parser: append_token malloc error");

    for (int j = 0; j < i; j++)
        new_cmd[j] = (*args)->cmd[j];

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
        // case TK_REDIR_HEREDOC:
        //     return QUOTE_HEREDOC;
        default:
            return UNKNOWN;
    }
}


// ファイルリダイレクトノードを追加する
void file_node_add(t_parser *args, char *filename, t_redirect_type type)
{
    t_file *file;
    t_file *cur;

    file = malloc(sizeof(t_file));
    if (!file)
        fatal_error("parser: file_node_add malloc error");

    file->filename = strdup(filename);
    file->type = type; // リダイレクトタイプの取得
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


void create_command(t_parser *args, t_token *token)
{
    t_token *tmp;
    t_parser *cur_arg;

    tmp = token;
    cur_arg = args;
    while (tmp->type != TK_EOF && tmp->type != TK_PIPE)
    {
        if (is_redirect(tmp))
            file_node_add(cur_arg, tmp->data, get_redirect_type(tmp->type));
        else
        {
            cur_arg = arg_node_add(cur_arg); // ノードを追加して、次のノードを返す
            append_token(&cur_arg, tmp); // トークンを追加
        }
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
}

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
    print_parser(args_head);
    // free_parser(args_head);
}
