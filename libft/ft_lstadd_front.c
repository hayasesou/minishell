/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:24:14 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/10 13:33:42 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// void display(t_list *lst)
// {
// 	while(lst)
// 	{
// 	char *s = (char *)lst ->content;
// 	printf("[%s]\n",s);
// 	lst = lst ->next;
// 	}
// }

// int main()
// {
// 	t_list *lst = NULL;
// 	t_list *new = ft_lstnew("hello");
// 	ft_lstadd_front(&lst,new);
// 	t_list *new2 = ft_lstnew("putain");
// 	ft_lstadd_front(&lst,new2);

// 	t_list *new3 = ft_lstnew("world");
// 	ft_lstadd_front(&lst,new3);
// 	display(lst);
// }

// void hirosuzu_test(t_list **lst, t_list *new)
// {
// 	printf("\nTEST START\n");
// 	ft_lstadd_front(lst,new);
// 	while (&(*lst)!= NULL)
// 	{
// 		printf("front = [%s]\n", (char *)(*lst)->content);
// 		lst = &(*lst)->next;
// 	}
// }

// int main()
// {
// 	t_list *a;

// 	a = ft_lstnew("I love");
// 	char test1[] = "hirosuzu";
// 	char test2[] = "";

// 	hirosuzu_test(&a, ft_lstnew(test1));
// 	hirosuzu_test(&a, ft_lstnew(test2));
// 	return (0);
// }

// void test(t_list *lst)
// {
// 	int i = 0;
// 	while(lst != NULL)
// 	{
// 		printf("%s\n",lst->content);
// 		lst = lst->next;
// 		i++;
// 	}
// }

// int main ()
// {

// 	t_list *list_1 ,*list_2,*list_3 ,*list_4;
// 	list_1 = ft_lstnew("hello");
// 	list_2 = ft_lstnew("domo");
// 	list_3 = ft_lstnew("nihao");
// 	list_1 -> next = list_2;
// 	list_2 -> next = list_3;
// 	list_3 -> next = NULL;
// 	list_4 = ft_lstnew("rikai");
// 	printf("\ntest start\n");
// 	test(list_1);
// 	ft_lstadd_front(&list_1, list_4);
// 	printf("\nfront\n");
// 	test(list_1);
// 	return(0);
// }