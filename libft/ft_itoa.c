/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:16:11 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 15:30:49 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n, int sign)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	if (sign == -1)
		count++;
	return (count);
}

static void	allocation(char *ret, long n, int digit, int sign)
{
	while (digit >= 0)
	{
		ret[digit] = n % 10 + '0';
		n = n / 10;
		digit--;
	}
	if (sign == -1)
		ret[digit + 1] = '-';
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*ret;
	int		digit;
	long	num;

	num = (long)n;
	sign = 1;
	if (num < 0)
	{
		sign = -1;
		num *= sign;
	}
	digit = count_digits(num, sign);
	ret = (char *)malloc(sizeof(char) * (digit + 1));
	if (ret == NULL)
		return (NULL);
	ret[digit] = '\0';
	allocation(ret, num, digit - 1, sign);
	return (ret);
}

// #include <stdio.h>

// void	test(int n)
// {
// 	char	*str;

// 	str = ft_itoa(n);
// 	printf("\n n = [%d]     str = [%s]\n", n, str);
// }

// int main()
// {
// 	test(123);
// 	test(-123);
// 	test(1);
// 	test(0);
// 	test(+123);
// 	test(-1234567890);
// }