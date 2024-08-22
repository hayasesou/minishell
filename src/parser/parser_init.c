#include "minishell.h"

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
