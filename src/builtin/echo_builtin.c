/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:53:40 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 19:53:41 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_option(char *op)
{
	int	i;

	i = 1;
	if (op[0] != '-')
		return (false);
	while (op[i] == 'n')
		i++;
	if (op[i] != '\0')
		return (false);
	return (true);
}

void	echo_builtin(t_parser *parser, t_context *context)
{
	int			i;
	bool		n_option;
	t_parser	*tmp_parser;

	i = 1;
	n_option = false;
	tmp_parser = parser;
	while (tmp_parser->cmd[i] && is_n_option(tmp_parser->cmd[i]))
	{
		n_option = true;
		i++;
	}
	while (tmp_parser->cmd[i])
	{
		ft_printf("%s", tmp_parser->cmd[i]);
		if (tmp_parser->cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n_option)
		ft_printf("\n");
	context->exit_status = 0;
}
