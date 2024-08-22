/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:26:55 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/24 16:48:14 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*s_c;
	size_t			j;

	j = 0;
	s_c = (unsigned char *)s;
	i = (unsigned int)c;
	while (j < n)
	{
		s_c[j] = i;
		j++;
	}
	return (s_c);
}

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// int main (void)
// {
// 	char s[10] = "123456789";
// 	char *s1 = malloc(2);
// 	memset(s1, 'a', 10000000000);
// 	printf("%s\n", s1);
// 	ft_memset(s, 'b', 11);
// 	printf("%s\n", s);
// 	return (0);
// }