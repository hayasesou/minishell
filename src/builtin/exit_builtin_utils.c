/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayase <hayase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:44:59 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/19 02:14:03 by hayase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

bool	overflow_check(long n, int n2, int flag)
{
	if ((n * flag > LONG_MAX / 10) || (n * flag == LONG_MAX / 10
			&& n2 > LONG_MAX % 10))
		return (true);
	if ((n * flag < LONG_MIN / 10) || (n * flag == LONG_MIN / 10 && n2 > -1
			* (LONG_MIN % 10)))
		return (true);
	return (false);
}

bool	is_overflow(char *str)
{
	long	num;
	int		flag;

	num = 0;
	flag = 1;
	while (*str == ' ')
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (overflow_check(num, *str - '0', flag))
			return (true);
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (false);
}

bool	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (false);
	if (str[i] == '\0')
		return (false);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}

void	cleanup_and_exit(t_context *context, int exit_status)
{
	free_all(context);
	exit(exit_status);
}
