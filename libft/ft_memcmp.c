/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:46:52 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 13:42:09 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sp1;
	unsigned char	*sp2;
	size_t			i;

	i = 0;
	sp1 = (unsigned char *)s1;
	sp2 = (unsigned char *)s2;
	while (i < n)
	{
		if (sp1[i] != sp2[i])
			return (sp1[i] - sp2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
//  int main ()
//  {
// 	char str1[] = "abcdef";
// 	char str2[] = "abcdef";

// 	printf("ori:%d    ft:%d\n",memcmp(str1,str2,3),ft_memcmp(str1,str2,3));
// 	printf("ori:%d    ft:%d\n",memcmp(str1,str2,5),ft_memcmp(str1,str2,5));
// 	puts("---------------");

// 	char str3[] = "abcdefg";
// 	char str4[] = "abcdef";

//    printf("ori:%d    ft:%d\n",memcmp(str3,str4,6),ft_memcmp(str3,str4,6));
// 	printf("ori:%d    ft:%d\n",memcmp(str3,str4,7),ft_memcmp(str3,str4,7));

// 	return(0);
//  }