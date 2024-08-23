#include "minishell.h"

bool	is_single_quote_closed(char *line)
{
	while (*line)
	{
		line++;
		if (*line == '\'')
			return (true);
	}
	printf("single quote is not closed\n");
	return (false);
}

bool	is_double_quote_closed(char *line)
{
	while (*line)
	{
		line++;
		if (*line == '\"')
			return (true);
	}
	printf("double quote is not closed\n");
	return (false);
}

char	*single_quote_removal(char *str)
{
	char	*start;

	str++;
	start = str;
	while (*str && !(is_single_quote(*str)))
		str++;
	if (is_single_quote(*str))
		return (strndup(start, str - start));
	else
		return (NULL);
}

char	*double_quote_removal(char *str)
{
	char	*start;

	str++;
	start = str;
	while (*str && !(is_double_quote(*str)))
		str++;
	if (is_double_quote(*str))
		return (strndup(start, str - start));
	else
		return (NULL);
}
void combine_adjacent_tokens(t_token *head)
{
    t_token *current = head;
    while (current && current->next)
    {
        if (is_combinable(current) && is_combinable(current->next))
        {
            char *combined = ft_strjoin(current->data, current->next->data);
            free(current->data);
            current->data = combined;
            current->type = TK_WORD;  // 結合されたトークンはWORDとして扱う

            t_token *to_delete = current->next;
            current->next = to_delete->next;
            if (current->next)
                current->next->prev = current;
            free(to_delete->data);
            free(to_delete);
        }
        else
        {
            current = current->next;
        }
    }
}

bool is_combinable(t_token *token)
{
    return token->type == TK_WORD || token->type == TK_SINGLE_QUOTE || token->type == TK_DOUBLE_QUOTE;
}

void combine_tokens(t_token *head)
{
    t_token *current = head;
    while (current && current->next)
    {
        if ((current->type == TK_WORD || current->type == TK_DOUBLE_QUOTE) && 
            (current->next->type == TK_WORD || current->next->type == TK_DOUBLE_QUOTE))
        {
            char *combined = ft_strjoin(current->data, current->next->data);
            free(current->data);
            current->data = combined;
            current->type = TK_DOUBLE_QUOTE;  // 結合されたトークンはダブルクォートとして扱う
            
            t_token *to_delete = current->next;
            current->next = to_delete->next;
            if (current->next)
                current->next->prev = current;
            free(to_delete->data);
            free(to_delete);
        }
        else
        {
            current = current->next;
        }
    }
}

// void quote(char **line_ptr, char *line, t_token *token)
// {
//     char quote_char = *line;
//     char *start = line + 1;  // クォートの次の文字から始める
//     line++;

//     while (*line && *line != quote_char)
//         line++;

//     if (*line == quote_char)
//     {
//         int length = line - start;  // クォートを含まない長さ
//         char *quoted_str = strndup(start, length);
//         if (quoted_str == NULL)
//             fatal_error("quote: strndup error");

//         t_token_type type = (quote_char == '\'') ? TK_SINGLE_QUOTE : TK_DOUBLE_QUOTE;
//         token_node_add(token, token_node_create(quoted_str, type));
//         free(quoted_str);
//         *line_ptr = line + 1;  // 終わりのクォートの次の文字へ
//     }
//     else
//     {
//         err_exit(start - 1, "Unclosed quote", 1);
//     }
// }

void quote(char **line_ptr, char *line, t_token *token, bool space_before)
{
    char quote_char = *line;
    char *start = line + 1;  // クォートの次の文字から始める
    line++;

    while (*line && *line != quote_char)
        line++;

    if (*line == quote_char)
    {
        int length = line - start;  // クォートを含まない長さ
        char *quoted_str = strndup(start, length);
        if (quoted_str == NULL)
            fatal_error("quote: strndup error");

        t_token_type type;
        if (quote_char == '\'')
            type = space_before ? TK_SPACE_SINGLE_QUOTE : TK_SINGLE_QUOTE;
        else
            type = space_before ? TK_SPACE_DOUBLE_QUOTE : TK_DOUBLE_QUOTE;

        token_node_add(token, token_node_create(quoted_str, type));
        free(quoted_str);
        *line_ptr = line + 1;  // 終わりのクォートの次の文字へ
    }
    else
    {
        err_exit(start - 1, "Unclosed quote", 1);
    }
}