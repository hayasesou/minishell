
#include "../include/struct.h"
#include "../include/lexer.h"

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

t_token	*add_token(char *data, t_token_type type, t_token_state state)
{
	t_token	*token;

	token = calloc(1, sizeof(*token));
	if (token == NULL)
		fatal_error("tokenize: add token calloc error");
	token->type = type;
	token->data = strdup(data);
	token->state = state;
	if (!token->data)
		perror("tokenize: add token strdup error");
	return (token);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	consume_blank(char **line_ptr, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*line_ptr = line;
		return (true);
	}
	*line_ptr = line; // これ必要？
	return (false);
}

bool	start_with_operator(const char *s, const char *operator)
{
	return (memcmp(s, operator, strlen(operator)) == 0);
}

bool	is_operator(const char *s)
{
	static char *const	operators[] = {"|", "&", "(", ")", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (start_with_operator(s, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

t_token	*operator(char **line_ptr, char *line)
{
	static char *const	operators[] = {"|", "&", "(", ")", "\n"};
	size_t				i;
	char				*op;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (start_with_operator(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("tokenize: operator, strdup error");
			*line_ptr = line + strlen(op);
			return (add_token(op, TK_OP));
		}
		i++;
	}
	//assert_error("tokenize: operator, unexpected operator");
	return (NULL); // errorにしておわらせる, 一時的にreturnを書かないと動かないからnull返している
}

bool	is_metacharacter(char c)
{
	return (c && strchr("|&;()<> \t\n", c));
}

bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	is_double_quote(char c)
{
	return (c == '\"');
}

t_token	*single_quote_removal(char **line_ptr, char *line)
{
	char	*start;
	t_token	*token;

	start = line;
	if (is_single_quote(*line))
	{
		start++;
		line++;
	}
	while (*line && !(is_single_quote(*line)))
		line++;
	if (is_single_quote(*line))
	{
		line++;
		line_ptr = line;
		return (strndup(start, line - start));
	}
	else
		return (NULL);
}

t_token	*double_quote_expansion(char **line_ptr, char *line)
{
	//  パラメータ展開について処理を追加する
	char	*start;
	t_token	*token;

	start = line;
	if (is_double_quote(*line))
	{
		start++;
		line++;
	}
	while (*line && !(is_double_quote(*line)))
		line++;
	if (is_double_quote(*line))
	{
		line++;
		line_ptr = line;
		return (strndup(start, line - start));
	}
	else
		return (NULL);
}

t_token	*word(char **line_ptr, char *line)
{
	const char	*start;
	char		*word;

	start = line;
	if (*line && is_single_quote(*line))
	{
		word = quote_removal(&line, line);
		if (word == NULL)
			printf("Unclosed single quote");
		return (add_token(word, TK_WORD, SINGLE_QUOTE));
	}
	else if (*line && is_double_quote(*line))
	{
		word = double_quote_expansion(&line, line);
		if (word == NULL)
			printf("Unclosed double quote");
		return (add_token(word, TK_WORD, DOUBLE_QUOTE));
	}
	while (*line && !is_metacharacter(*line))
		line++; // 普通の文字の時
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("tokenize: word strndup error");
	*line_ptr = line;
	return (add_token(word, TK_WORD, GENERAL));
}
