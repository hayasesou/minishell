/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:57:19 by hfukushi          #+#    #+#             */
/*   Updated: 2023/07/16 13:06:10 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_p;
	char	letter;

	letter = c;
	s_p = (char *)s;
	while (*s_p != '\0' && *s_p != letter)
		s_p++;
	if (*s_p == letter)
		return (s_p);
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	char s1[] = "abcde";
// 	char c = 'b';
// 	char *p ;

// 	p = ft_strchr(s1,c);
// 	printf("%s\n",p);
// 	puts("----");
// 	p = ft_strchr(NULL,c);
// 	printf("%s\n",p);
// 	puts("----");
// 		p = ft_strchr(s1,'\0');
// 	printf("%s\n",p);
// }
