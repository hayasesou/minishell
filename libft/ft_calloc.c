/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:50:16 by hfukushi          #+#    #+#             */
/*   Updated: 2023/09/20 11:18:02 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*p;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	p = (void *)malloc(size * count);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, size * count);
	return (p);
}

// #include <stdio.h>

// int main()
// {
// 	void	*actual = ft_calloc(42,1);
// 	void	*expected = calloc(42, 1);
// 	printf("ft :%p \nori :%p",actual,expected);
// 	free(actual);
// 	free(expected);
// 	return(0);
// }