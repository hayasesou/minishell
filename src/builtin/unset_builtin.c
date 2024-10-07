#include	"minishell.h"

void	unset_builtin(t_parser *parser, t_context *context)
{
	t_env	*env_tmp;
	t_env	*env_prev;

	env_tmp = context->env_head->next;
	env_prev = context->env_head;
	while (env_tmp != context->env_head)
	{
		if (ft_strncmp(env_tmp->env_name, parser->cmd[1],
				ft_strlen(parser->cmd[1])) == 0
			&& ft_strlen(parser->cmd[1]) == ft_strlen(env_tmp->env_name))
		{
			env_prev->next = env_tmp->next;
			free(env_tmp->env_name);
			free(env_tmp->env_val);
			free(env_tmp);
			break ;
		}
		env_tmp = env_tmp->next;
		env_prev = env_prev->next;
	}
	context->exit_status = SUCCESS;
}
