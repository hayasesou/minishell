/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:37:33 by hakobaya          #+#    #+#             */
/*   Updated: 2024/06/29 21:17:55 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/lexer.h"
#include "struct_test.h"

t_token	*token_init(void)
{
	t_token	*head;

	head = calloc(1, sizeof(t_token));
	if (!head)
	{
		perror("calloc error in tokenize : token_init ");
		exit (1); // 後でちゃんとしたエラーに修正
	}
	return (head);
}

t_token	*add_token(char *data, t_token_type type)
{
	t_token	*token;

	token = calloc(1, sizeof(*token));
	if (token == NULL)
		fatal_error("tokenize: add token calloc error");
	token->type = type;
	token->data = strdup(data);
	if (!token->data)
		perror("tokenize: add token strdup error");
	return (token);
}

t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*token;

	//head = token_init();
	head.next = NULL;
	token = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line))
		{
			token = token->next;
			token = operator(&line, line);
		}
		else if (is_word(line))
		{
			token = token->next;
			token = word(&line, line);
		}
		else
			assert_error("tokenize: unexpected token");
	}
	token->next = add_token(NULL, TK_EOF);
	return (head.next);
}


//gcc main.c -lreadline

// static void	shell_loop(char *line)
// {
// 	add_history(line);
// }

void	free_tokens(t_token *token)
{
	t_token *tmp;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		free(tmp);
	}
}

int	main(void)
{
	char	*line;
	t_token	*tokens;

	rl_outstream = stderr;
	printf("a\n");
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
		{
			tokens = tokenize(line);
			// トークン処理のデバッグ出力
			for (t_token *token = tokens; token; token = token->next)
			{
				printf("Token type: %d, data: %s\n", token->type, token->data);
			}
			free_tokens(tokens);
		}
		free(line);
	}
	exit(0);
}
