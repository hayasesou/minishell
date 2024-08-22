/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 05:40:32 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 14:46:42 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (p == NULL)
		return (p);
	while (i < s1_len + s2_len)
	{
		if (i < s1_len)
			p[i] = s1[i];
		else
			p[i] = s2[i - s1_len];
		i++;
	}
	p[i] = '\0';
	return (p);
}
