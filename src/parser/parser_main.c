#include "minishell.h"

t_token    *cat_token(t_token *token)
{
    t_token *new_token;
    t_token *tmp;

    while (token->next != TK_EOF && is_string(token))
    {
        if (is_cat_token(token))
            new_token = strjoin(token->data, token->next->data);
        else if (token->type == TK_WORD && token->next->type == TK_WORD)
        {
            token = strjoin(token->data, " ");
            new_token = strjoin(token->data, token->next->data);
        }
        else
            break;
        token = token->next;
    }
    return (new_token);
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

void    arg_node_create(t_parser **args, t_token *token)
{
    t_parser    *new_arg;

    new_arg = (t_parser *)malloc(sizeof(t_parser));
    if (new_arg == NULL)
        fatal_error("parser: arg_node_create malloc error");
    
}

void    arg_node_add(t_parser *args, t_token *token)
{
    t_parser    *node;

    if (is_string(token))
    {
        append_token(token);
        arg_node_add(args, token);
    }
    else if (is_redirect(token))
        arg_node_add(args, token);
    else if (is_pipe(token))
        arg_node_add(args, token);
    else
        err_exit(token, "parser: arg_node_add invalid token type", 0);
}

void    file_node_add(char *filename, int type)
{
    t_parser    *node;

    node = malloc(sizeof(t_file));
    node->filename = strdup(filename);
    node->type = type;
    node->next = NULL;
}

void    create_command(t_parser *args_head, t_token *token)
{
    t_token *tmp;

    tmp = token;
    while (tmp->type != TK_EOF)
    {
        if (is_redirect(tmp))
            parse_redirect();
        else if (is_pipe(tmp))
            parse_pipe();
        else
            parse_cmd();
        tmp = tmp->next;
    }
}

void    command_init(t_parser *parser)
{
    parser->cmd = malloc(sizeof(char *) * 2);
    if (parser->cmd == NULL)
        return (fatal_error("parser: command init malloc error"));
        
}

void    parser(t_context *ctx)
{
    t_parser    *args;
    t_parser    *args_head;
    t_token     *token;

    args = args_init();
    if (args == NULL)
        fatal_error("parser: parser is NULL"); // 合ってる？
    args_head = parser;
    token = ctx->token_head->next; // token head用のtoken_type作成するかTK_EMPTYのままにするかあとで考える
    while (token->type != TK_EOF)
    {
        arg_node_add(&args, token);
        token = token->next;
    }
    // print_parser(parser_head);
}