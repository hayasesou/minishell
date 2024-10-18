/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:37:30 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 00:37:31 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(char *file_name)
{
	ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
}

void	unexisted_env_error(char *env)
{
	ft_printf("minishell: %s: ambiguous redirect\n", env);
}
