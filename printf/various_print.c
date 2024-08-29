/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   various_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:07:41 by hfukushi          #+#    #+#             */
/*   Updated: 2023/09/06 12:48:42 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_percent(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (0);
	else
		return (1);
}

void	fft_putnbr_fd(int n, int fd, int *len)
{
	char	digit;
	long	num;

	num = (long)n;
	if (num < 0)
	{
		if (write(fd, "-", 1) == -1)
			return ;
		num *= -1;
		(*len)++;
	}
	digit = num % 10 + '0';
	if (num / 10 != 0)
	{
		fft_putnbr_fd(num / 10, fd, len);
	}
	if (write(fd, &digit, 1) == -1)
		return ;
	else
		(*len)++;
}

int	fft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	while (*s != '\0')
	{
		if (write(fd, s, 1) == -1)
			return (len);
		len++;
		s++;
	}
	return (len);
}

void	ft_putunbr_fd(unsigned int n, int fd, int *len)
{
	char			digit;
	unsigned long	num;

	num = (unsigned long)n;
	digit = num % 10 + '0';
	if (num / 10 != 0)
	{
		ft_putunbr_fd(num / 10, fd, len);
	}
	if (write(fd, &digit, 1) == -1)
		return ;
	else
		(*len)++;
}

void	put_c(char c, int *len)
{
	if (write(1, &c, 1) != -1)
		(*len)++;
}
