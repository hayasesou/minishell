/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 03:15:52 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/10 04:20:08 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// void test()
// {
// 	t_list  *lst_0;
// 	t_list  *lst_1;
// 	t_list  *lst_2;

// 	lst_0 = ft_lstlast(NULL);
// 	printf("last node is [%p]\n",lst_0 );  //NULL

// 	lst_1 = ft_lstnew("eringi");
// 	t_list *lst_1last = ft_lstlast(lst_1);
// 	printf("last node is [%s]\n",lst_1last -> content); //1こだけ

// 	lst_2 = ft_lstnew("makroni");
// 	ft_lstadd_front(&lst_1,lst_2);
// 	t_list *lst_2last = ft_lstlast(lst_1);
// 	printf("last node is [%s]\n",lst_2last -> content); //makaroni eringi

// }

// int main()
// {
// 	test();
// 	return (0);
// }