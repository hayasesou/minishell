#include "../include/minishell.h"

static void    free_env_node(t_env *node)
{
    free(node->env_name);
    node->env_name = NULL;
    free(node->env_val);
    node->env_val = NULL;
    free(node);
    node = NULL;
}

static void    free_env(t_context *context)
{
    t_env    *tmp;
    t_env    *head;
    t_env    *delete;

    if (context->env_head == NULL)
        return ;
    head = context->env_head;
    tmp = head->next;
    while (tmp->next != NULL)
    {
        delete = tmp;
        head->next = tmp->next;
        tmp->next->prev = head;
        tmp = tmp->next;
        free_env_node(delete);
    }
    free_env_node(tmp);
}

static void    free_token(t_token *token_head)
{
    t_token    *tmp;
    t_token    *delete;

    if (token_head == NULL)
        return ;
    tmp = token_head->next;
    while (tmp != token_head)
    {
        delete = tmp;
        token_head->next = tmp->next;
        tmp->next->prev = token_head;
        tmp = tmp->next;
        free(delete->data);
        free(delete);
    }
    free(token_head->data);
    free(token_head);
}

static void    free_cmd(char **cmd)
{
    size_t    i;

    i = 0;
    if (cmd == NULL)
        return ;
    while (cmd[i])
    {
        free(cmd[i]);
        cmd[i] = NULL;
        i++;
    }
    free(cmd);
    cmd = NULL;
}

static void    free_all(t_context *context)
{
//    free_cmd(context->parser_head->cmd); //context構造体変更したら
//    free_token(context->token_head); // これも必要になりそう
    free_env(context->env_head);
}
