/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:45:43 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 13:27:54 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	char	upper;

	if (97 <= c && c <= 122)
	{
		upper = -32 + (char)c;
		return (upper);
	}
	return (c);
}
