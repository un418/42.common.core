/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 23:54:18 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:39:32 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_lstadd_back - Add node at end of linked list

DESCRIPTION 
 Adds the node ’new’ at the end of the list.

PARAMETERS
 - lst: The address of a pointer to the first node of a list.
 - new: The address of a pointer to the node to be added.

RETURN VALUE
 - None
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
