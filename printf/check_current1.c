/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_current1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:56:29 by hfukushi          #+#    #+#             */
/*   Updated: 2023/09/06 12:48:11 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check(const char **fmt, va_list *ap)
{
	int	len;

	len = 0;
	if (**fmt == 'c')
		put_c((char)va_arg(*ap, int), &len);
	else if (**fmt == 's')
		len += fft_putstr_fd((char *)va_arg(*ap, char *), 1);
	else if (**fmt == 'd' || **fmt == 'i')
		fft_putnbr_fd((int)va_arg(*ap, int), 1, &len);
	else if (**fmt == 'u')
		ft_putunbr_fd((unsigned int)va_arg(*ap, unsigned int), 1, &len);
	else if (**fmt == 'x' || **fmt == 'X')
		ft_put16basenbr_fd((unsigned int)va_arg(*ap, unsigned int),
			&len, "0123456789ABCDEF", **fmt);
	else if (**fmt == 'p')
		ft_p((unsigned long long)va_arg(*ap, unsigned long long),
			&len, "0123456789abcdef", **fmt);
	else if (**fmt == '%')
		len += ft_percent('%', 1);
	else
		return (len);
	(*fmt)++;
	return (len);
}
