/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 02:07:54 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/11 23:18:03 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (count);
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// void	list_display(t_list *lst)
// {
// 	int	count;

// 	count = 0;
// 	while (lst)
// 	{
// 		count++;
// 		printf("%s\n", lst->content);
// 		lst = lst->next;
// 	}
// 	printf("size: %d\n", count);
// }

// void	test_1(void)
// {
// 	t_list	*lst;
// 	t_list	*tmp;
// 	t_list  *tmp2;

// 	list_display(NULL);
// 	printf("ft_lstsize: %d\n", ft_lstsize(NULL));

// 	printf("add\n");
// 	lst = ft_lstnew("hello");
// 	list_display(lst);
// 	printf("ft_lstsize: %d\n", ft_lstsize(lst));

// 	printf("\nadd\n");
// 	tmp = ft_lstnew("world");
// 	ft_lstadd_front(&lst, tmp);
// 	list_display(lst);
// 	printf("ft_lstsize: %d\n", ft_lstsize(lst));

// 	printf("\nadd\n");
// 	tmp2 = ft_lstnew("\0");
// 	ft_lstadd_front(&lst, tmp2);
// 	list_display(lst);
// 	printf("ft_lstsize: %d\n", ft_lstsize(lst));
// }

// int main ()
// {
// 	test_1();
// }
