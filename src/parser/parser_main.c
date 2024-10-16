/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:43:54 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:43:55 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_redirect(t_parser *cur_arg, t_token *token)
{
	t_file	*new_file;
	t_file	*last;

	new_file = (t_file *)malloc(sizeof(t_file));
	if (new_file == NULL)
		return (0);
	new_file->filename = ft_strdup(token->next->data);
	if (!new_file->filename)
	{
		free(new_file);
		return (0);
	}
	new_file->type = get_redirect_type(token->type);
	new_file->heredoc_fd = -1;
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
	return (1);
}

static void	handle_pipe(t_parser **args, t_token **token)
{
	t_parser	*new_args;

	new_args = args_init();
	if (new_args == NULL)
	{
		fprintf(stderr, "Parser initialization error\n");
		return ;
	}
	(*args)->next = new_args;
	new_args->prev = *args;
	*args = new_args;
	*token = (*token)->next;
}

t_parser	*args_init(void)
{
	t_parser	*args;

	args = (t_parser *)malloc(sizeof(t_parser));
	if (args == NULL)
		fatal_error("parser: args init malloc error");
	args->cmd = NULL;
	args->file = NULL;
	args->next = NULL;
	args->prev = NULL;
	return (args);
}

void	parser(t_context *ctx)
{
	t_parser	*args;
	t_parser	*args_head;
	t_token		*token;

	args = args_init();
	if (args == NULL)
		fatal_error("args_init malloc error");
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
	ctx->parser_head = args_head;
}
