/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:36:13 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/10 14:50:04 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dest;

	if (s == NULL || f == NULL)
		return (NULL);
	dest = ft_strdup(s);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (dest[i] != '\0')
	{
		dest[i] = (*f)(i, dest[i]);
		i++;
	}
	return (dest);
}
