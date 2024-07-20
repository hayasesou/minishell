#include "../../include/minishell.h"

void	print_enum(t_token *node)
{
	if (node->type == TK_EMPTY)
		printf(" %s\n", "EMPTY");
	else if (node->type == TK_PIPE)
		printf(" %s\n", "PIPE");
	else if (node->type == TK_SINGLE_QUOTE)
		printf(" %s\n", "SINGLE QUOTE");
	else if (node->type == TK_DOUBLE_QUOTE)
		printf(" %s\n", "DOUBLE QUOTE");
	else if (node->type == TK_REDIR_IN)
		printf(" %s\n", "REDIRECT IN");
	else if (node->type == TK_REDIR_HEREDOC)
		printf(" %s\n", "HEREDOC");
	else if (node->type == TK_REDIR_OUT)
		printf(" %s\n", "REDIRECT OUT");
	else if (node->type == TK_REDIR_APPEND)
		printf(" %s\n", "APPEND");
	else
		// print_enum_utils(node);
		printf("word\n");
}

void	print_lexer(t_token *token_head)
{
	t_token	*tmp;

	tmp = token_head->next;
	while (tmp != token_head)
	{
		printf("%s:", tmp->data);
		print_enum(tmp);
		tmp = tmp->next;
	}
}
