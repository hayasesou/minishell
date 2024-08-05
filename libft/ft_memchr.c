/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:16:01 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 13:39:53 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sp;
	size_t			i;
	unsigned char	cp;

	i = 0;
	sp = (unsigned char *)s;
	cp = (unsigned char)c;
	while (i < n)
	{
		if (*sp == cp)
			return (sp);
		sp++;
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

//  int main ()
//  {
// 		char *s = calloc(30, sizeof(char));
// 	memcpy(s, "libft-test-tokyo", 17);
// 	memcpy(s + 20, "acdfg", 5);
// 	printf("%s\n",ft_memchr(s, 'i', 30));
// 	printf("%s\n",memchr(s, 'i', 30));

// 	puts("===================================");

// 	printf("%s\n",memchr(s, 'z', 30));
// 	printf("%s\n",ft_memchr(s, 'z', 30));
//  }