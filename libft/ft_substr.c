/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 02:49:10 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 14:40:45 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
		len = 0;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (s[i + start] != '\0' && i < len)
		{
			str[i] = s[i + start];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>

// void	test(char const *s, unsigned int start, size_t len)
// {
// 	printf(">> %s %d %zu\n", s, start, len);
// 	char *ret = ft_substr(s, start, len);

// 	int i = 0;
// 	while (1)
// 	{
// 		printf("%d\n", i);
// 		if (ret[i] == '\0')
// 			break ;
// 		printf("%c", ret[i]);
// 		i++;
// 	}
// 	printf("[%s]\n", ret);
// }

// int main ()
// {
// 	test("libft-test-tokyo", 0, 100);
// }
// [test 5] ASSERT_EQ_STR failed: ("s/test_ft_substr.c") is not
//equal to expected (""). func main at file srcs/test_ft_substr.c,
// line 22
// [test 10] ASSERT_EQ_STR failed: ("s/tes") is not equal to expected
// (""). func main at file srcs/test_ft_substr.c,
// line 27