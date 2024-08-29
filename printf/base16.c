/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base16.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:17:07 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/26 12:59:44 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// void	ft_put16basenbr_fd(unsigned int n, int *len, char *baseHexadecimal,
// 		char conbersion)
// {
// 	char				digit;
// 	unsigned long long	num;

// 	num = (unsigned long long)n;
// 	digit = baseHexadecimal[num % 16];
// 	if (digit >= 'A' && digit <= 'F' && conbersion == 'x')
// 		digit += 32;
// 	(*len)++;
// 	if (num / 16 != 0)
// 		ft_put16basenbr_fd(num / 16, len, baseHexadecimal, conbersion);
// 	if (conbersion == 'p' && num / 16 == 0)
// 		(*len) += write(1, "0x", 2);
// 	ft_putchar_fd(digit, 1);
// }
void	ft_put16basenbr_fd(unsigned int n, int *len, char *baseHexadecimal,
		char conbersion)
{
	char				digit;
	unsigned long long	num;

	num = (unsigned long long)n;
	digit = baseHexadecimal[num % 16];
	if (digit >= 'A' && digit <= 'F' && conbersion == 'x')
		digit += 32;
	if (num / 16 != 0)
		ft_put16basenbr_fd(num / 16, len, baseHexadecimal, conbersion);
	if (write(1, &digit, 1) == -1)
		return ;
	else
		(*len)++;
}

// void	ft_p(unsigned long long n, int *len, char *baseHexadecimal,
// 		char conbersion)
// {
// 	char				digit;
// 	unsigned long long	num;

// 	num = (unsigned long long)n;
// 	digit = baseHexadecimal[num % 16];
// 	(*len)++;
// 	if (num / 16 != 0)
// 		ft_p(num / 16, len, baseHexadecimal, conbersion);
// 	if (num / 16 == 0)
// 		(*len) += write(1, "0x", 2);
// 	ft_putchar_fd(digit, 1);
// }
void	ft_p(unsigned long long n, int *len, char *baseHexadecimal,
		char conbersion)
{
	char				digit;
	unsigned long long	num;

	num = (unsigned long long)n;
	digit = baseHexadecimal[num % 16];
	if (num / 16 != 0)
		ft_p(num / 16, len, baseHexadecimal, conbersion);
	if (num / 16 == 0)
	{
		if (write(1, "0x", 2) == -1)
			return ;
		else
			(*len) += 2;
	}
	if (write(1, &digit, 1) == -1)
		return ;
	else
		(*len)++;
}
