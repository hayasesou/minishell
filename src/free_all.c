#include "minishell.h"

void free_token(t_token **head_ref)
{
    t_token *cur;
    t_token *next;
	t_token *head;

	head = *head_ref;
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
	*head_ref = NULL;
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

void free_parser(t_parser **head_ref)
{
    t_parser *tmp;
    t_parser *delete;
    int i;

    if (*head_ref == NULL)
        return;
    tmp = *head_ref;
    while(tmp != NULL)
    {
        i = 0;
        if (tmp->cmd != NULL)
        {
            while(tmp->cmd[i] != NULL)
                free(tmp->cmd[i++]);
            free(tmp->cmd);
			tmp->cmd = NULL;
        }
        if (tmp->file != NULL)
        {
            free_file(tmp->file);
			tmp->file = NULL;
        }
        delete = tmp;
        tmp = tmp->next;
        free(delete);
    }
	*head_ref = NULL;
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
        free_token(&(ctx->token_head));
        ctx->token_head = NULL;
    }
    if (ctx->parser_head != NULL)
    {
	free_parser(&(ctx->parser_head));
        ctx->parser_head = NULL;
    }
    free(ctx);
}
