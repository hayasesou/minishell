/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:26:43 by hfukushi          #+#    #+#             */
/*   Updated: 2023/08/22 18:27:53 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	long	num;

	num = (long)n;
	if (num < 0)
	{
		num *= -1;
		print('-', fd);
	}
	digit = num % 10 + '0';
	if (num / 10 != 0)
	{
		ft_putnbr_fd(num / 10, fd);
	}
	print(digit, fd);
}

// void test(int n)
// {
// 	ft_putnbr_fd(n,1);
// }

// int main()
// {
// 	test(100);
// 	return(0);
// }
