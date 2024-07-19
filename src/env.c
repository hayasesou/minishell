#include "../include/minishell.h"

t_env	*node_new_set(t_env *env_node, char *str)
{
	// dupする部分調べる
	env_node->env_name = strdup(str);
	if (env_node->env_name == NULL)
		return (NULL);
	env_node->env_val = strdup(str);
	if (env_node->env_val == NULL)
		return (NULL);
	return (env_node);
}

t_env	*node_new(char *str)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (env_node == NULL)
		return (NULL);
	if (strlen(str) == 0)
	{
		env_node->env_name = NULL;
		env_node->env_val = NULL;
	}
	else
	{
		env_node = node_new_set(env_node, str);
		if (env_node == NULL)
			return (NULL);
	}
	env_node->next = NULL;
	env_node->prev = NULL;
	return (env_node);
}

t_env	*env_head_init(void)
{
	t_env	*head;

	head = node_new("");
	if (head == NULL)
		return (NULL);
	head->next = head;
	head->prev = head;
	return (head);
}

void	node_add(t_env *head, t_env *new)
{
	if (head == NULL || new == NULL)
		return ;
	new->next = head;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*new;
	int		i;

	i = 0;
	head = env_head_init();
	while (envp[i])
	{
		new = node_new(envp[i]);
		if (new == NULL)
		{
			// free_env_all
			return (NULL);
		}
		node_add(head, new);
		i++;
	}
	return (head);
}
