/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 04:29:13 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 10:51:25 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char			*z;
	unsigned int	i;

	i = 0;
	z = (char *)s;
	while (i < n)
	{
		z[i] = '\0';
		i++;
	}
}

// #include <stdio.h>
// #include <strings.h>

// int main()
// {
// 	char s[] = "hello";
// 	ft_bzero(s, 0);
// 	printf("%s\n", s);
// 	bzero(s, 0);
// 	printf("%s\n", s);
// 	char t[] = "hello-world";
// 	ft_bzero(t, 5);
// 	printf("%s\n", t);
// 	bzero(t, 5);
// 	printf("%s\n", t);
// 	return (0);
// }