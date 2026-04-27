/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:22:00 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/27 13:45:02 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_lstiter - Applies f function to the content of a node and it's successors

DESCRIPTION
 Iterates through the list ’lst’ and applies the function ’f’ 
  to the content of each node.
PARAMETERS
 - lst: The address of a pointer to a node.
 - f: The address of the function to apply to each node’s content.
RETURN VALUE
 None
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*next;

	if (!lst)
		return ;
	while (lst)
	{
		next = (lst)->next;
		f(lst->content);
		(lst) = next;
	}
}
