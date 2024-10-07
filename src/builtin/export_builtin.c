#include "minishell.h"

void	export_builtin(t_parser *parser, t_context *context)
{
	if (parser->cmd == NULL)
		return ;
	else if (parser->cmd[1] == NULL)
		no_arg_export(context->env_head);
	else
		arg_export(context->env_head, parser->cmd[1], context);
}
