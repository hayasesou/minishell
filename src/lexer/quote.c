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

// クォート内の文字列を抽出する関数
char *extract_quoted_str(char *start, int length) {
    if (length > 0)
        return ft_strndup(start, length);
    return ft_strdup("");
}

// クォート文字とスペースの有無に基づいてトークンタイプを決定する関数
t_token_type determine_token_type(char quote_char, bool space_before) {
    if (quote_char == '\'')
        return space_before ? TK_SPACE_SINGLE_QUOTE : TK_SINGLE_QUOTE;
    else
        return space_before ? TK_SPACE_DOUBLE_QUOTE : TK_DOUBLE_QUOTE;
}

void quote(char **line_ptr, char *line, t_token *token, bool space_before)
{
    char            quote_char;
    char            *start;
    char            *quoted_str;
	int				length;
    t_token_type    type;

	quote_char = *line;
	start = line + 1;
	line++;
    while (*line && *line != quote_char)
        line++;
    if (*line == quote_char)
    {
        length = line - start;
        quoted_str = extract_quoted_str(start, length);
        if (!quoted_str)
            fatal_error("quote: ft_strdup error");
        type = determine_token_type(quote_char, space_before);
        token_node_add(token, token_node_create(quoted_str, type));
        free(quoted_str);
        *line_ptr = line + 1;
    }
    else
        err_exit(start - 1, "Unclosed quote", 1);
}