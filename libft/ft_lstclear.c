/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 01:37:56 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:39:15 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_lstclear - delete properly a node and it's successors from a t_list

DESCRIPTION 
 Deletes and frees the given node and all its successors,
  using the function ’del’ and free(3).
 Finally, set the pointer to the list to NULL.

PARAMETERS
 - lst: The address of a pointer to a node.
- del: The address of the function used to delete the content of the node.

RETURN VALUE
 - None
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}
