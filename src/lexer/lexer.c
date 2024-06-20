/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:37:33 by hakobaya          #+#    #+#             */
/*   Updated: 2024/06/20 23:50:51 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

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

t_token	*tokenize(char *line)
{
	t_token	*head;
	t_token	*cur;

	head = token_init();
	cur = &head;

	while (*line++)
	{
		if (*line == ' ' || *line == '\t')
			continue ;
		else if (*line == '<' && *(line + 1) == ' ')
			cur = add_token(TK_REDIR_IN, cur, line++);
		else if (*line == '>' && *(line + 1) == ' ')
			cur = add_token(TK_REDIR_OUT, cur, line++);
		else if (*line == '>' && *(line + 1) == '>')
		{
			cur = add_token(TK_REDIR_APPEND, cur, line++);
			line++;
		}
		else if (*line == '<' && *(line + 1) == '<')
		{
			cur = add_token(TK_REDIR_HEREDOC, cur, line++);
			line++;
		}
		else if (*line == '|')
			cur = add_token(TK_PIPE, cur, line++);
		else
			cur = add_token(TK_WORD, cur, line++);
		// 多分この単語の部分をどうにかしないとダメ、'や"も含むのと、スペースまで読み続けるべきかもしれない
	}
	add_token(TK_EOF, cur, line);
	return (head->next);
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
