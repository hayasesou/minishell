/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 05:59:47 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/12 09:43:58 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (*del == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
}

// //メモリーリークをなくす

// void free_string(void *raw)
// {
// 	char * str;
// 	str = (char *)raw;
// 	free(str);
// }

// void free_int(void *raw)
// {
// 	int * i;
// 	i = (int *)raw;
// 	free(i);
// }

// void test2(void *data)
// {
// 	t_list lst_1;

// 	lst_1 = ft_lstnew(data);
// 	ft_lstdelone(lst_1,)
// }

// void test3(void *data)
// {
// 	t_list lst_1;

// 	lst_1 = ft_lstnew(data);
// 	ft_lstdelone(lst_1,)
// }

// int main()
// {

// 	test2("hello");
// 	test3(12345);
// 	return(0);
// }