/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:37:06 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/27 21:13:57 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_lstmap - 

PARAMETERS
 - lst: The address of a pointer to a node.
 - f: The address of the function applied to each node’s content.
 - del: The address of the function used to delete a node’s content if needed.
RETURN VALUE
 - The new list.
 - NULL if the allocation fails.
DESCRIPTION
 Create a new list resulting of the successive applications of the function ’f’
  through the list ’lst’, applies the function ’f’ to each node’s content,
 The ’del’ function is used to delete the content of a node if needed.

*/

#include "libft.h" 

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist_cur;
	t_list	*newlist_start;
	t_list	*newnode;
	t_list	*newcontent;

	newlist_cur = NULL;
	newlist_start = NULL;
	while (lst)
	{
		newcontent = f(lst->content);
		newnode = ft_lstnew(newcontent);
		if (!newnode)
		{
			del(newcontent);
			ft_lstclear(&newlist_start, del);
			return (NULL);
		}
		if (!newlist_start)
			newlist_start = newnode;
		else
			newlist_cur->next = newnode;
		newlist_cur = newnode;
		lst = lst->next;
	}
	return (newlist_start);
}
