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

static void add_command(t_parser *cur_arg, t_token *token)
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
    new_cmd[i] = strdup(token->data);
    new_cmd[i + 1] = NULL;
    free(cur_arg->cmd);
    cur_arg->cmd = new_cmd;
}

void create_command(t_parser *args, t_token *token)
{
    t_token *tmp;
    t_parser *cur_arg;

    tmp = token;
    cur_arg = args;
    while (tmp != NULL && tmp->type != TK_EOF && tmp->type != TK_PIPE)
    {
        if (is_redirect(tmp))
        {
            if (tmp->next == NULL)
            {
                fprintf(stderr, "Syntax error near unexpected token `newline'\n");
                return;
            }
            add_redirect(cur_arg, tmp);
            tmp = tmp->next;
        }
        else if (is_string(tmp))
            add_command(cur_arg, tmp);
        tmp = tmp->next;
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
