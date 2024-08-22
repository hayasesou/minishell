/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:20:40 by hfukushi          #+#    #+#             */
/*   Updated: 2023/06/10 13:33:15 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

// #include <stdio.h>

// void	display(t_list	*lst)
// {
// 	int		i = 0;

// 	printf("\n");
// 	while (lst)
// 	{
// 		printf("[%d]: %s\n", i, (char *)lst->content);
// 		i++;
// 		lst = lst->next;
// 	}
// }

// int		is_alpha(int c)
// {
// 	return ('a' <= c && c <= 'z');
// }

// void	*to_upper(void *content)
// {
// 	char	*str = (char *)content;
// 	char	*new_content;

// 	str = ft_strdup(str);
// 	new_content = (void *)str;
// 	while (*str)
// 	{
// 		if (is_alpha(*str))
// 			*str = *str - ('a' - 'A');
// 		str++;
// 	}
// 	return (new_content);
// }

// void	del(void *content)
// {
// 	free(content);
// 	return ;
// }

// int		main(void)
// {
// 	t_list	*lst = NULL;
// 	t_list	*node;

// 	node = ft_lstnew(ft_strdup("hello"));
// 	ft_lstadd_back(&lst, node);
// 	node = ft_lstnew(ft_strdup("hi"));
// 	ft_lstadd_back(&lst, node);
// 	node = ft_lstnew(ft_strdup("putain"));
// 	//node->content = to_upper(node->content);
// 	ft_lstadd_back(&lst, node);
// 	node = ft_lstnew(ft_strdup("!!!"));
// 	ft_lstadd_back(&lst, node);

// 	display(lst);

// 	t_list	*ret = ft_lstmap(lst, to_upper, del);

// 	display(ret);
// }
