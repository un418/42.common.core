/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:21:24 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/25 17:46:20 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_lstadd_front() - Add node at start of linked list

DESCRIPTION
 Adds the node ’new’ at the beginning of the list.
PARAMETERS
 - lst: The address of a pointer to the first node of a list.
 - new: The address of a pointer to the node to be added.
*/

#include "libft.h"

void ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
