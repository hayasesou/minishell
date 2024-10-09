#include "minishell.h"

void free_token(t_token *head)
{
    t_token *cur;
    t_token *next;

    if (head == NULL)
        return;
    cur = head->next;
    while(cur != head)
    {
        next = cur->next;
        free(cur->data);
        free(cur);
        cur = next;
    }
    free(head->data);
    free(head);
}

void free_file(t_file *head)
{
	t_file	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->filename != NULL)
			free(tmp->filename);
		free(tmp);
	}
}

void free_parser(t_parser *head)
{
    t_parser *tmp;
    t_parser *delete;
    int i;

    if (head == NULL)
        return;
    tmp = head;
    while(tmp != NULL)
    {
        i = 0;
        if (tmp->cmd != NULL)
        {
            while(tmp->cmd[i] != NULL)
                free(tmp->cmd[i++]);
            free(tmp->cmd);
        }
        if (tmp->file != NULL)
            free_file(tmp->file);
        delete = tmp;
        tmp = tmp->next;
        free(delete);
    }
}

void free_env_node(t_env *node)
{
	if (node == NULL)
		return ;
	free(node->env_name);
	node->env_name = NULL;
	free(node->env_val);
	node->env_val = NULL;
	free(node);
	node = NULL;
}

void free_env(t_env *head)
{
    t_env	*cur;
    t_env	*next;

	cur = head->next;
    if (head == NULL)
        return;
    while (cur != head)
    {
        next = cur->next;
        free_env_node(cur);
        cur = next;
    }
    free_env_node(head);
}

void free_all(t_context *ctx)
{
    if (ctx == NULL)
        return;
    if (ctx->env_head != NULL)
    {
        free_env(ctx->env_head);
        ctx->env_head = NULL;
    }
    if (ctx->token_head != NULL)
    {
        free_token(ctx->token_head);
        ctx->token_head = NULL;
    }
    if (ctx->parser_head != NULL)
    {
        free_parser(ctx->parser_head);
        ctx->parser_head = NULL;
    }
    free(ctx);
}

// void    exit_free(t_context *ctx)
// {
//     free_all(ctx);
//     exit(1);
// }
