#include "../../include/minishell.h"

void	print_enum(t_token *node)
{
	if (node->type == TK_EMPTY)
		printf("type [%s]\n", "EMPTY");
	else if (node->type == TK_PIPE)
		printf("type [%s]\n", "PIPE");
	else if (node->type == TK_SINGLE_QUOTE)
		printf("type [%s]\n", "SINGLE QUOTE");
	else if (node->type == TK_DOUBLE_QUOTE)
		printf("type [%s]\n", "DOUBLE QUOTE");
	else if (node->type == TK_REDIR_IN)
		printf("type [%s]\n", "REDIRECT IN");
	else if (node->type == TK_REDIR_HEREDOC)
		printf("type [%s]\n", "HEREDOC");
	else if (node->type == TK_REDIR_OUT)
		printf("type [%s]\n", "REDIRECT OUT");
	else if (node->type == TK_REDIR_APPEND)
		printf("type [%s]\n", "APPEND");
	else
		// print_enum_utils(node);
		printf("type [%s]\n", "WORD");
}

void	print_lexer(t_token *token_head)
{
	t_token	*tmp;

	tmp = token_head->next;
	while (tmp->type != TK_EOF)
	{
		printf("data [%s] : ", tmp->data);
		print_enum(tmp);
		tmp = tmp->next;
	}
}
