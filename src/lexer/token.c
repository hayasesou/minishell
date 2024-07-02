//#include "../../include/lexer.h"
#include "struct_test.h"

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
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

void	append_ch

void	quote_removal(t_token *token)
{
	char	*removed_token;
	char	*p;

	if (token == NULL || token->type != TK_WORD || token->data == NULL)
		return ;
	p = token->data;
	removed_token = NULL;
	while (*p && !is_metacharacter(*p))
	{
		if (is_quote(*p))
		{
			p++;
			while (*p != is_quote(*p))
			{
				if (*p == '\0')
					printf("Unclosed quote");

			}
		}
	}
}

t_token	*word(char **line_ptr, char *line)
{
	const char	*start;
	char		*word;

	start = line;
	while (*line && !is_metacharacter(*line))
	{
		if (*line && is_quote(*line))
		{
			line++; // シングルクオート一つ分進める
			while (*line && !is_quote(*line))
				line++;
			if (*line == '\0')
				printf("Unclosed single quote"); // ここをどうにか処理する（多分入力を待ち続ける？）
			else
				line++; // 閉じた分のシングルクオートを進める
		}
		line++; // 普通の文字の時
	}
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("tokenize: word strndup error");
	*line_ptr = line;
	return (add_token(word, TK_WORD));
}
