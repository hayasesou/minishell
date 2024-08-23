#include "minishell.h"

static void add_redirect(t_parser *cur_arg, t_token *token)
{
    t_file *new_file;
    t_file *last;

    new_file = malloc(sizeof(t_file));
    if (new_file == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }
    new_file->filename = strdup(token->next->data);
    new_file->type = get_redirect_type(token->type);
    new_file->next = NULL;
    if (cur_arg->file == NULL)
        cur_arg->file = new_file;
    else
    {
        last = cur_arg->file;
        while (last->next != NULL)
            last = last->next;
        last->next = new_file;
    }
}

void add_command(t_parser *cur_arg, char *cmd_str)
{
    char **new_cmd;
    int i;

    i = 0;
    while (cur_arg->cmd && cur_arg->cmd[i])
        i++;
    new_cmd = malloc(sizeof(char *) * (i + 2));
    if (new_cmd == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }
    i = 0;
    while (cur_arg->cmd && cur_arg->cmd[i])
    {
        new_cmd[i] = cur_arg->cmd[i];
        i++;
    }
    new_cmd[i] = strdup(cmd_str);
    new_cmd[i + 1] = NULL;
    free(cur_arg->cmd);
    cur_arg->cmd = new_cmd;
}

void create_command(t_parser *args, t_token *token)
{
    t_token *tmp;
    t_parser *cur_arg;
    char *combined_str;

    tmp = token;
    cur_arg = args;
    combined_str = NULL;
    while (tmp != NULL && tmp->type != TK_EOF && tmp->type != TK_PIPE)
    {
        if (is_redirect(tmp))
        {
            add_redirect(cur_arg, tmp);
            tmp = tmp->next->next;
        }
        else if (is_string(tmp))
        {
            if (!combined_str)
                combined_str = strdup(tmp->data);
            else
                join_words(&combined_str, &tmp);
            tmp = tmp->next;
            // 次のトークンがスペースない場合は結合を続ける
            while (tmp && is_space_string(tmp))
            {
                join_words(&combined_str, &tmp);
                tmp = tmp->next;
            }
            add_command(cur_arg, combined_str);
            free(combined_str);
            combined_str = NULL;
        }
        else
            tmp = tmp->next;
    }
    if (combined_str)
    {
        add_command(cur_arg, combined_str);
        free(combined_str);
    }
}

static void handle_pipe(t_parser **args, t_token **token)
{
    t_parser *new_args;

    new_args = args_init();
    if (new_args == NULL)
    {
        fprintf(stderr, "Parser initialization error\n");
        return;
    }
    (*args)->next = new_args;
    new_args->prev = *args;
    *args = new_args;
    *token = (*token)->next;
}

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

void parser(t_context *ctx)
{
    t_parser *args;
    t_parser *args_head;
    t_token *token;

    args = args_init();
    if (args == NULL)
    {
        fprintf(stderr, "Parser initialization error\n");
        return;
    }
    args_head = args;
    token = ctx->token_head->next;
    while (token != NULL && token->type != TK_EOF)
    {
        create_command(args, token);
        while (token != NULL && token->type != TK_PIPE && token->type != TK_EOF)
            token = token->next;
        if (token != NULL && token->type == TK_PIPE)
            handle_pipe(&args, &token);
    }
    print_parser(args_head);
    // free_parser(args_head);
}
