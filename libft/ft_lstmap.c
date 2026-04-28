/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:37:06 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:36:49 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
ft_lstmap - Create a new list resulting resulting of 
  f function to the content of a node and it's successors

DESCRIPTION
  Create a new list resulting of the successive applications of the function ’f’
   through the list ’lst’, applies the function ’f’ to each node’s content,
  The ’del’ function is used to delete the content of a node if needed.

PARAMETERS
 - lst: The address of a pointer to a node.
 - f: The address of the function applied to each node’s content.
 - del: The address of the function used to delete a node’s content if needed.

IMPLEMENTATION NOTES
 Deliberatly choose to not use ft_lstadd_back() to preserve performance
  when working on large linked list.

RETURN VALUE
 - Pointer to the beginning new list.
 - NULL if the allocation fails.
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
