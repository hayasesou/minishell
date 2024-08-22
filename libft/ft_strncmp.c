/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 08:16:32 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/24 16:56:12 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				j;
	unsigned char	*str1;
	unsigned char	*str2;

	j = 0;
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		j = (int)str1[i] - (int)str2[i];
		if (j != 0)
			return (j);
		i++;
	}
	return (j);
}

/*
int	main(void)
{
	char	*cmp2 = calloc(10, 1);

	int ret = ft_strncmp(cmp2, "abcd", 10);

	printf("%d\n", ret);
}*/

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int main()
// {
// 	char s1[] = "abcdefghi";
// 	char s2[] = "abcdefhhi";
// 	int judge;
// 	int judge2;

// 	judge = strncmp(s1,s2,0);
// 	judge2 = ft_strncmp(s1,s2,0);
// 	printf("%d   %d\n",judge , judge2);

// 	puts("------");

// 	judge = strncmp(s1,s2,2);
// 	judge2 = ft_strncmp(s1,s2,2);
// 	printf("%d   %d\n",judge, judge2);

// 	puts("------");

// 	judge = strncmp(s1,s2,7);
// 	judge2 = ft_strncmp(s1,s2,7);
// 	printf("%d   %d\n",judge, judge2);

// 	puts("------");

// 	judge = strncmp(s1,s2,9);
// 	judge2 = ft_strncmp(s1,s2,9);
// 	printf("%d   %d\n",judge, judge2);

// 	puts("------");

// 	char s3[] = "abcdefhhi";
// 	char s4[] = "abcdefhgh";
// 	judge = strncmp(s3,s4,9);
// 	judge2 = ft_strncmp(s3,s4,9);
// 	printf("%d   %d\n",judge, judge2);

// 	puts("------");

// 	char s5[] = "abcdefghi";
// 	char s6[] = "abcdefghi";
// 	judge = strncmp(s5,s6,17);
// 	judge2 = ft_strncmp(s5,s6,17);
// 	printf("%d   %d\n",judge, judge2);

// 	puts("------");
// 	char *str = "libft-test-tokyo";
// 	int	len = strlen(str);
// 	char *cmp2 = calloc(10, 1);
// 	strlcpy(cmp2, "libft", 10);

// 	cmp2[5] = -128;
// 	printf("%d\n",ft_strncmp(str, cmp2, len));
// }
