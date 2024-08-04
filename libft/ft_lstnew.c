/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 07:10:22 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/19 19:25:40 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

// void test(char *content)
// {
// 	t_list *list =  ft_lstnew(content);
// 	printf("[%s]\n",list->content);
// }

// int main ()
// {
// 	test("hello");
// 	test(NULL);
// 	test("hello world");
// 	test("");
// 	test("\n");
// 	return (0);
// }