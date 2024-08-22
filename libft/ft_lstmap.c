/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:04:47 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/12 00:23:58 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;

	new_lst = NULL;
	if (lst == NULL || *(*f) == NULL || (*del) == NULL)
		return (NULL);
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (node == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		lst = lst->next;
	}
	return (new_lst);
}

// void display(t_list *lst)
// {
// 	printf("\n");
// 	while(lst)
// 	{
// 	int s = (int)lst ->content;
// 	printf("[%d]\n",s);
// 	lst = lst ->next;
// 	}
// }

// void no(void * k)
// {
// 	(void )k;
// 	return ;
// }

// void *changesign(void * content)
// {
// 	long long num = (long long)content;
// 	num *=-1;
// 	return ((void *)num);
// }

// int main()
// {
// 	t_list *lst = NULL;
// 	t_list *new = ft_lstnew((void*)1);
// 	ft_lstadd_front(&lst,new);
// 	t_list *new2 = ft_lstnew((void *)2);
// 	ft_lstadd_front(&lst,new2);

// 	t_list *new3 = ft_lstnew((void *)3);
// 	ft_lstadd_front(&lst,new3);
// 	display(lst);

// 	t_list *newlst;
// 	newlst = ft_lstmap(lst,changesign,no);
// 	display(newlst);
// }