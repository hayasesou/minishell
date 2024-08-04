/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 10:15:35 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 14:49:24 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	front(char const *s1, char const *set)
{
	int	front_len;

	front_len = 0;
	while (ft_strchr(set, *s1))
	{
		if (*s1 == '\0')
			return (-1);
		front_len++;
		s1++;
	}
	return (front_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				front_len;
	int				rear_len;
	unsigned int	s1_len;
	char			*p;

	if (s1 == NULL || set == NULL)
		return (NULL);
	p = (char *)s1;
	s1_len = ft_strlen(s1);
	front_len = 0;
	rear_len = 0;
	if (*s1 == '\0')
		return (ft_strdup(""));
	front_len = front(s1, set);
	if (front_len == -1)
		return (ft_strdup(""));
	while (ft_strchr(set, *(s1 + s1_len)))
	{
		rear_len++;
		s1--;
	}
	return (ft_substr(p, front_len, s1_len + 1 - front_len - rear_len));
}

// #include <stdio.h>

// void test(char const *s1, char const *set)
// {
// 	printf(">> %s %s\n", s1, set);
// 	char *ret = ft_strtrim(s1, set);
// 	printf("[%s]\n", ret);
// }

// int main ()
// {
// 	test("hello world","world");
// 	test("hello world","hello world");
// 	test("hello world","");
// 	test("", "");
// 	test("    hello world     ", " ");
// }