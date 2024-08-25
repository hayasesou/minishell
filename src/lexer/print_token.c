#include "minishell.h"

void print_enum(t_token *node)
{
    switch(node->type)
    {
        case TK_WORD:
            printf("type [WORD]\n");
            break;
        case TK_SPACE_WORD:
            printf("type [SPACE WORD]\n");
            break;
        case TK_SINGLE_QUOTE:
            printf("type [SINGLE QUOTE]\n");
            break;
        case TK_SPACE_SINGLE_QUOTE:
            printf("type [SPACE SINGLE QUOTE]\n");
            break;
        case TK_DOUBLE_QUOTE:
            printf("type [DOUBLE QUOTE]\n");
            break;
        case TK_SPACE_DOUBLE_QUOTE:
            printf("type [SPACE DOUBLE QUOTE]\n");
            break;
        case TK_PIPE:
            printf("type [PIPE]\n");
            break;
        case TK_REDIR_IN:
            printf("type [REDIRECT IN]\n");
            break;
        case TK_REDIR_OUT:
            printf("type [REDIRECT OUT]\n");
            break;
        case TK_REDIR_APPEND:
            printf("type [APPEND]\n");
            break;
        case TK_REDIR_HEREDOC:
            printf("type [HEREDOC]\n");
            break;
        case TK_EOF:
            printf("type [EOF]\n");
            break;
        case TK_EMPTY:
            printf("type [EMPTY]\n");
            break;
        default:
            printf("type [UNKNOWN(%d)]\n", node->type);
    }
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
