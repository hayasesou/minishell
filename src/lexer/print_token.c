#include "minishell.h"

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
	else if (node->type == TK_WORD)
		printf("type [%s]\n", "WORD");
	else if (node->type == TK_EOF)
		printf("type [%s]\n", "TK_EOF");
}

void print_lexer(t_token *token_head)
{
    t_token *tmp;

    tmp = token_head->next;
    while (tmp != NULL)
    {
        printf("data [%s] : ", tmp->data ? tmp->data : "(null)");
        print_enum(tmp);
        if (tmp->next == NULL)
            printf("token->next is NULL\n");
        if (tmp->type == TK_EOF) // TK_EOF トークンに達した場合にループを終了
            break;
        tmp = tmp->next;
    }
}
