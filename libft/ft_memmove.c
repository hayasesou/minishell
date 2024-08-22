/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:18:54 by hfukushi          #+#    #+#             */
/*   Updated: 2023/05/21 19:09:07 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

// difference between memcpy and memmove -> https://mogachan.net/clangmemcpy/

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*src_p;
	char	*dst_p;

	src_p = (char *)src;
	dst_p = (char *)dest;
	if (src_p < dst_p)
	{
		while (0 < len)
		{
			dst_p[len - 1] = src_p[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dst_p, src_p, len);
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	unsigned int len = 0;
// 	char src[100] = "abcdeghij";
// 	char dst[100] = "123456789";
// 	char src_2[100] = "abcdeghij";
// 	char dst_2[100] = "123456789";
// 	ft_memmove(dst, src, len);
// 	printf("%s\n", dst);
// 	memmove(dst_2 , src_2, len);
// 	printf("%s\n", dst_2);

// 	puts("-----");

// 	len = 5;
// 	ft_memmove(dst, src, len);
// 	printf("%s\n", dst);
// 	memmove(dst_2 , src_2, len);
// 	printf("%s\n", dst_2);

// 	puts("-----");

// 	len = 100;
// 	ft_memmove(dst, src, len);
// 	printf("%s\n", dst);
// 	memmove(dst_2 , src_2, len);
// 	printf("%s\n", dst_2);

// 	puts("-----");

// 	ft_memmove(dst, dst+2, 50);
// 	printf("%s\n", dst);
// 	memmove(dst_2, dst_2+2, 50);
// 	printf("%s\n", dst_2);

// 	return (0);
// }