/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:24:14 by hfukushi          #+#    #+#             */
/*   Updated: 2023/09/06 12:47:59 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	put_c(char c, int *len);
int		ft_percent(char c, int fd);
void	fft_putnbr_fd(int n, int fd, int *len);
void	ft_putunbr_fd(unsigned int n, int fd, int *len);
int		fft_putstr_fd(char *s, int fd);
int		ft_printf(const char *fmt, ...);
int		check(const char **fmt, va_list *ap);
void	ft_put16basenbr_fd(unsigned int n, int *len,
			char *baseHexadecimal, char conbersion);
void	ft_p(unsigned long long n, int *len,
			char *baseHexadecimal, char conbersion);

#endif