#include "minishell.h"

bool	is_operator(char c)
{
	return (c && strchr("|<>", c)); // \n\tは必要かどうか
}

bool	is_available_operator(char *line)
{
	if (line[0] == '|' && !is_operator(line[1]))
		return (true);
	else if (line[0] == '<')
	{
		if (!is_operator(line[1]) || (line[1] == '<' && !is_operator(line[2])))
			return (true);
	}
	else if (line[0] == '>')
	{
		if (!is_operator(line[1]) || (line[1] == '>' && !is_operator(line[2])))
			return (true);
	}
	return (false);
}

char	*select_op(char *line)
{
	char	*op;

	if (line[0] == '|' && !is_operator(line[1]))
		op = "|";
	else if (line[0] == '<')
	{
		if (!is_operator(line[1]))
			op = "<";
		if (line[1] == '<' && !is_operator(line[2]))
			op = "<<";
	}
	else if (line[0] == '>')
	{
		if (!is_operator(line[1]))
			op = ">";
		if (line[1] == '>' && !is_operator(line[2]))
			op = ">>";
	}
	else
		return (NULL); // どうする
	return (op);
}

t_token_type	select_op_type(char *op)
{
	if (strcmp(op, "|") == 0)
		return (TK_PIPE);
	if (strcmp(op, "<") == 0)
		return (TK_REDIR_IN);
	if (strcmp(op, ">") == 0)
		return (TK_REDIR_OUT);
	if (strcmp(op, "<<") == 0)
		return (TK_REDIR_HEREDOC);
	if (strcmp(op, ">>") == 0)
		return (TK_REDIR_APPEND);
	return (TK_EMPTY); // errorの場合どうすればいい
}

void	operator(char **line_ptr, char *line, t_token *token)
{
	char			*op;
	t_token_type	type;

	if (is_available_operator(line))
	{
		op = select_op(line);
		type = select_op_type(op);	
	}
	else
		err_exit(line, "operatorが有効じゃありません", 0) ; // error変更した方がいい
	token_node_add(token, token_node_create(op, type, GENERAL));
	//assert_error("tokenize: operator, unexpected operator");
	*line_ptr += strlen(op);
}
