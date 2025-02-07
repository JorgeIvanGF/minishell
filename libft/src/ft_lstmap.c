/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:40:08 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/15 19:42:37 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.*/

static void	*ft_n_content_works(void *content, t_list *n_lst,
	void (*del)(void *))
{
	if (!content)
	{
		ft_lstclear(&n_lst, del);
		return (NULL);
	}
	return (content);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_node;
	t_list	*n_lst;
	void	*n_content;

	n_lst = NULL;
	while (lst)
	{
		n_content = f(lst->content);
		if (!(ft_n_content_works(n_content, n_lst, del)))
			return (NULL);
		n_node = malloc(sizeof(t_list));
		if (!n_node)
		{
			del(n_content);
			ft_lstclear(&n_lst, del);
			return (NULL);
		}
		n_node->content = n_content;
		n_node->next = NULL;
		ft_lstadd_back(&n_lst, n_node);
		lst = lst->next;
	}
	return (&*n_lst);
}
