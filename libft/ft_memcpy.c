/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:33:16 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/24 15:38:39 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest_s;
	char	*src_s;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (dst);
	i = 0;
	dest_s = (char *)dst;
	src_s = (char *)src;
	while (i < n)
	{
		dest_s[i] = src_s[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char dst[11] = "yahooooooo";
// 	char src[13] = "yeeeeeeeeeee";
// 	char dst_2[11] = "yahooooooo";
// 	char src_2[13] = "yeeeeeeeeeee";
// 	// ft_memcpy(NULL, NULL, 2);
// 	// printf("%s\n", dst);
// 	memcpy(NULL, NULL, 2);
// 	printf("%s\n", dst_2);

// 	puts("-----");

// 	ft_memcpy(dst, src, 5);
// 	printf("%s\n", dst);
// 	memcpy(dst_2, src_2, 5);
// 	printf("%s\n", dst_2);

// 	puts("-----");

// 	// ft_memcpy(dst, src, 15);
// 	// printf("%s\n", dst);
// 	// memcpy(dst_2, src_2, 15);
// 	// printf("%s\n", dst_2);

// 	// puts("-----");

// 	// ft_memcpy(NULL, src, 20);
// 	// printf("%s\n", dst);
// 	// memcpy(NULL, src_2, 20);
// 	// printf("%s\n", dst_2);
// }