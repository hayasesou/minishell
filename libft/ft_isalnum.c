/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:19:51 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/24 16:23:07 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	c;
// 	c = 'a';
// 	printf("%d\n", ft_isalnum(c));
// 	c = 'A';
// 	printf("%d\n", ft_isalnum(c));
// 	c = '0';
// 	printf("%d\n", ft_isalnum(c));
// 	c = '*';
// 	printf("%d\n", ft_isalnum(c));
// 	return(0);
// }