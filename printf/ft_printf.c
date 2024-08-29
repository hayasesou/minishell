/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:33:30 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/26 13:30:17 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_normal_str(const char **fmt, char **start)
{
	int	len;

	while (**fmt != '%' && **fmt)
	{
		(*fmt)++;
	}
	if (write(1, *start, *fmt - *start) == -1)
		return (-1);
	len = *fmt - *start;
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*start;
	int		write_len;

	write_len = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		start = (char *)fmt;
		if (*fmt != '%')
			write_len += print_normal_str(&fmt, &start);
		else
		{
			fmt++;
			write_len += check(&fmt, &ap);
		}
	}
	return (write_len);
}

// #include <limits.h>
// #include <unistd.h>

// int main()
// {
// 	int a;
// 	// ft_printf("12\\34%c%s%d%i%u%x%X%p%%"
// ,'h',"ok",0,INT_MAX,UINT_MAX,14,UINT_MAX,&a);
// 	// printf("12\\34%c%s%d%i%u%x%X%p%%"
// ,'h',"ok",0,INT_MAX,UINT_MAX,14,UINT_MAX,&a);

// 	printf("%d\n",ft_printf("12345\n%c\n%s\n%s\n
// %d\n%i\n%u\n%x\n%X\n%p\n%%",'k',"str",NULL,INT_MAX,1,UINT_MAX,10,10,&a));
// 	printf("%d\n",
//   printf("12345\n%c\n%s\n%s\n%d\n%i\n%u\n%x\n
// %X\n%p\n%%",'k',"str",NULL,INT_MAX,1,UINT_MAX,10,10,&a));

//    printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%
		// %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%\n", 'A', "42", 42, 42 ,42 , 42,
		// 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
// ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%
// 		%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%\n", 'A', "42", 42, 42 ,42 , 42,
// 		42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
// //     printf("%lx\n",LONG_MAX);
// //     ft_printf("%x\n",LONG_MAX);
// // 		printf("%lx\n",LONG_MIN);
// //     ft_printf("%x\n",LONG_MIN);

// // 		printf("%lx\n",ULONG_MAX);//27
// //     ft_printf("%x\n",ULONG_MAX);

// // 		printf("%llx\n",9223372036854775807LL);//28
// //     ft_printf("%x\n",9223372036854775807LL);
// 	return(0);
// }

// // c = (char)va_arg(ap,char)はNG ->  c = (char)va_arg(ap,int) OK