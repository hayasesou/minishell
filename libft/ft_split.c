/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:25:11 by hfukushi          #+#    #+#             */
/*   Updated: 2023/09/20 15:43:41 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char s, char d)
{
	if (s == d)
		return (1);
	return (0);
}

static size_t	count_strings(char *s, char d)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (is_delimiter(s[i], d))
			i++;
		else
		{
			count++;
			while (!is_delimiter(s[i], d))
			{
				if (s[i] == '\0')
					break ;
				i++;
			}
		}
	}
	return (count);
}

static size_t	word_len(char *s, char d)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (!is_delimiter(s[i], d) && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	**create2darray(char **ret, char *s, char d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] && is_delimiter(s[i], d))
			i++;
		if (s[i])
		{
			ret[j] = ft_substr(s, i, word_len(&s[i], d));
			if (ret[j] == NULL)
			{
				while (j-- >= 0)
					free(ret[j]);
				free(ret);
				return (NULL);
			}
			j++;
		}
		while (s[i] && !is_delimiter(s[i], d))
			i++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char		**ret;
	size_t		count;

	if (s == NULL)
		return (NULL);
	count = count_strings((char *)s, c) + 1;
	ret = (char **)ft_calloc(count, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	ret = create2darray(ret, (char *)s, c);
	return (ret);
}

// void	test(const char *str, int c)
// {
// 	char	**ret;
// 	int		i;

// 	printf("\n> str [%s] c [%c]\n", str, c);
// 	ret = ft_split(str, c);
// 	i = 0;
// 	while (ret[i])
// 	{
// 		printf("%s\n", ret[i]);
// 		i++;
// 	}
// }
// int	main(void)
// {
// 	test("hello world", ' '); //normal
// 								// test("   hello world", ' '); //front
// 								// test("hello world  ", ' ');//rear
// 								// test("         ", ' '); //allDelimniter
// 								// test(" ",'\0');
// 								// test("hello	world",'\0'); //tab
// 								// test("hello		world",'\0');
// 								// test("123456789012345678901234567890", 1);
// }