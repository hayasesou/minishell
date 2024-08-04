/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:07:15 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/24 16:41:19 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t destsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (destsize == 0)
		return (src_len);
	while (i < destsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>

// int main(void)
// {
// 	char *dest = "world";
// 	char *src = "zzzzzzzzzz";
// 	ft_strlcpy(dest, src, 0);
// 	printf("%s", dest);
// }

// int main(void){
// 	char *src = "Hello";
// 	char dst[10];
// 	char dst2[10];

// 	size_t size = 10;
// 	printf("%zu    %s\n",ft_strlcpy(dst, src, size),dst);
// 	printf("%zu    %s\n", strlcpy(dst2, src, size),dst2);

// 	puts("-----");

// 	size = 5;
// 	printf("%zu    %s\n",ft_strlcpy(dst, src, size),dst);
// 	printf("%zu    %s\n", strlcpy(dst2, src, size),dst2);

// 	puts("-----");

// 	printf("%zu    %s\n",ft_strlcpy(dst, src, size),dst);
// 	printf("%zu    %s\n", strlcpy(dst2, src, size),dst2);

// 	puts("-----");
// 	printf("%zu    %s\n",ft_strlcpy(NULL, src, size),dst);
// 	printf("%zu    %s\n", strlcpy(NULL, src, size),dst2);

// 	puts("-----");

// 	printf("%zu    %s\n",ft_strlcpy(dst, src, 0),dst);
// 	printf("%zu    %s\n", strlcpy(dst2, src, 0),dst2);
// }
