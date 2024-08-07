
#include "minishell.h"

static void	print_parser_type(t_redirect_type type)
{
	if (type == QUOTE_HEREDOC)
		printf("type = QUOTE_HEREDOC	:");
	else if (type == HEREDOC)
		printf("type = HEREDOC	:");
	else if (type == IN_FILE)
		printf("type = IN_FILE		:");
	else if (type == OUT_FILE)
		printf("type = OUT_FILE		:");
	else if (type == APPEND)
		printf("type = APPEND	:");
	else
		printf("type = ERROR	:");
}

static void	print_parser_file(t_file *file)
{
	t_file	*file_tmp;

	file_tmp = file;
	while (file_tmp != NULL)
	{
		print_parser_type(file_tmp->type);
		printf("%s\n", file_tmp->filename);
		file_tmp = file_tmp->next;
	}
}

void	print_parser(t_parser *parser_head)
{
	t_parser	*parser_tmp;
	int			i;

	parser_tmp = parser_head;
	while (parser_tmp != NULL)
	{
		printf("---------- pipe result ---------\n");
		i = 0;
		if (parser_tmp->cmd != NULL)
		{
			while (parser_tmp->cmd[i] != NULL)
			{
				printf("cmd[%d] = %s\n", i, parser_tmp->cmd[i]);
				i++;
			}
		}
		printf("files\n");
		print_parser_file(parser_tmp->file);
		parser_tmp = parser_tmp->next;
		printf("---------- pipe end ---------\n");
	}
}
