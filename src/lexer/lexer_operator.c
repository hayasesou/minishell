#include "minishell.h"

bool	is_operator(char c)
{
	return (c && ft_strchr("|<>", c));
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

char *select_op(char *line)
{
    if (line[0] == '|' && !is_operator(line[1]))
        return ft_strdup("|");
    else if (line[0] == '<')
    {
        if (line[1] == '<' && !is_operator(line[2]))
            return ft_strdup("<<");
        return ft_strdup("<");
    }
    else if (line[0] == '>')
    {
        if (line[1] == '>' && !is_operator(line[2]))
            return ft_strdup(">>");
        return ft_strdup(">");
    }
    return NULL;
}

t_token_type select_op_type(char *op)
{
    if (ft_strncmp(op, "|", 1) == 0 && op[1] == '\0')
        return TK_PIPE;
    else if (ft_strncmp(op, "<", 1) == 0 && op[1] == '\0')
        return TK_REDIR_IN;
    else if (ft_strncmp(op, ">", 1) == 0 && op[1] == '\0')
        return TK_REDIR_OUT;
    else if (ft_strncmp(op, "<<", 2) == 0 && op[2] == '\0')
        return TK_REDIR_HEREDOC;
    else if (ft_strncmp(op, ">>", 2) == 0 && op[2] == '\0')
        return TK_REDIR_APPEND;
    return TK_EMPTY;
}

void	operator(char **line_ptr, char *line, t_token *token)
{
	char			*op;
	t_token_type	type;

	if (is_available_operator(line))
	{
		op = select_op(line);
        if (!op)
            fatal_error("operator: select_op error");
		type = select_op_type(op);	
		token_node_add(token, token_node_create(op, type));
		*line_ptr += ft_strlen(op);
        free(op);
	}
	else
		err_exit(line, "operatorが有効じゃありません", 0) ; // エラー時にプログラムを終了
}
