/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:19:53 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 13:52:24 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_overflow(int sign, long *num, int digit);

int	ft_atoi(const char *str)
{
	int		sign;
	long	num;

	num = 0;
	sign = 1;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (handle_overflow(sign, &num, *str - '0'))
			break ;
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((int)(num * sign));
}

static int	handle_overflow(int sign, long *num, int digit)
{
	if (*num * sign > LONG_MAX / 10 || (*num * sign == LONG_MAX / 10
			&& digit > LONG_MAX % 10))
	{
		*num = LONG_MAX;
		return (1);
	}
	if (*num * sign < LONG_MIN / 10 || (*num * sign == LONG_MIN / 10
			&& (-digit) < LONG_MIN % 10))
	{
		*num = LONG_MIN;
		return (1);
	}
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	// /* 1 */ printf("%d      %d\n",ft_atoi(""), atoi(""));
// 	// /* 2 */ printf("%d      %d\n",ft_atoi("-"), atoi("-"));
// 	// /* 3 */ printf("%d      %d\n",ft_atoi("+"), atoi("+"));
// 	// /* 4 */ printf("%d      %d\n",ft_atoi("0"), atoi("0"));
// 	// /* 5 */ printf("%d      %d\n",ft_atoi("-0"), atoi("-0"));
// 	// /* 6 */ printf("%d      %d\n",ft_atoi("+0"), atoi("+0"));
// 	// /* 7 */ printf("%d      %d\n",ft_atoi("1"), atoi("1"));
// 	// /* 8 */ printf("%d      %d\n",ft_atoi("-1"), atoi("-1"));
// 	// /* 9 */ printf("%d      %d\n",ft_atoi("+1"), atoi("+1"));
// 	// /* 10 */ printf("%d      %d\n",ft_atoi("7"), atoi("7"));
// 	// /* 11 */ printf("%d      %d\n",ft_atoi("-7"), atoi("-7"));
// 	// /* 12 */ printf("%d      %d\n",ft_atoi("+7"), atoi("+7"));
// 	// /* 13 */ printf("%d      %d\n",ft_atoi("42"), atoi("42"));
// 	// /* 14 */ printf("%d      %d\n",ft_atoi("-42"), atoi("-42"));
// 	// /* 15 */ printf("%d      %d\n",ft_atoi("a"), atoi("a"));
// 	// /* 16 */ printf("%d      %d\n",ft_atoi("!"), atoi("!"));
// 	// /* 17. INT_MAX */ printf("%d      %d\n",ft_atoi("2147483647"),
// atoi("2147483647"));
// 	// /* 18. INT_MIN */ printf("%d      %d\n",ft_atoi("-2147483648"),
// atoi("-2147483648"));
// 	// /* 19. UINT_MAX */ printf("%d      %d\n",ft_atoi("4294967295"),
// atoi("4294967295"));
// 	// /* 20. LONG_MAX */ printf("%d      %d\n",ft_atoi("9223372036854775807"),
// atoi("9223372036854775807"));
// 	// /* 21. LONG_MIN */ printf("%d      %d\n",ft_atoi("-9223372036854775808"),
// atoi("-9223372036854775808"));
// 	// /* 22. ULONG_MAX */ printf("%d
// 			%d\n",ft_atoi("18446744073709551615"),
// 			atoi("18446744073709551615"));
//  /* 23. SIZE_MAX */ printf("%d      %d\n",ft_atoi("18446744073709551615"),
// 			atoi("18446744073709551615"));

// // 	// /* 24. INT_MAX + 1 */ printf("%d      %d\n",atoi("2147483648"),
// 			ft_atoi("2147483648"));
// // 	// /* 25. INT_MIN - 1 */ printf("%d      %d\n",atoi("-2147483649"),
// 			ft_atoi("-2147483649"));
// // 	// /* 26. UINT_MAX + 1 */ printf("%d      %d\n",atoi("4294967296"),
// 			ft_atoi("4294967296"));
// /* 27. LONG_MAX + 1 */ printf("%d      %d\n",atoi("9223372036854775808"),
// 			ft_atoi("9223372036854775808"));       // B
// // 	// /* 28. LONG_MIN - 1 */ printf("%d
// 			%d\n",atoi("-9223372036854775809"),
// 			ft_atoi("-9223372036854775809"));
// // 	// /* 29. ULONG_MAX + 1 */ printf("%d
// 			%d\n",atoi("18446744073709551616"),
// 			ft_atoi("18446744073709551616"));
// // 	// /* 30. SIZE_MAX + 1 */ printf("%d
// 			%d\n",atoi("18446744073709551616"),
// 			ft_atoi("18446744073709551616"));     // B

// // 	// /* 31. INT_MAX - 1 */ printf("%d      %d\n",atoi("2147483646"),
// 			ft_atoi("2147483646"));
// // 	// /* 32. INT_MIN + 1 */ printf("%d      %d\n",atoi("-2147483647"),
// 			ft_atoi("-2147483647"));
// // 	// /* 33. UINT_MAX - 1 */ printf("%d      %d\n",atoi("4294967294"),
// 			ft_atoi("4294967294"));
//  /* 34. LONG_MAX - 1 */ printf("%d      %d\n",atoi("9223372036854775806"),
// 			ft_atoi("9223372036854775806"));
// // 	// /* 35. LONG_MIN + 1 */ printf("%d
// 			%d\n",atoi("-9223372036854775807"),
// 			ft_atoi("-9223372036854775807"));
// /* 36. ULONG_MAX - 1 */ printf("%d      %d\n",atoi("18446744073709551614"),
// 			ft_atoi("18446744073709551614"));    // B
///* 37. SIZE_MAX - 1 */ printf("%d      %d\n",atoi("18446744073709551614"),
// 			ft_atoi("18446744073709551614"));     // B

///* 38. Many zeros 1*/ printf("%d      %d\n",atoi("000000000000000000008"),
// 			ft_atoi("000000000000000000008"));
///* 39. Many zeros 2*/ printf("%d      %d\n",atoi("-000000000000000000008"),
// 			ft_atoi("-000000000000000000008"));
///* 40. Many zeros 3*/ printf("%d      %d\n",atoi("+000000000000000000008"),
// 			ft_atoi("+000000000000000000008"));
// // 	return(0);
// // }