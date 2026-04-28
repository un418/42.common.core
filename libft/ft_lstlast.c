/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:48:42 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:38:30 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_lstlast - Return the adress of the last node of a list

DESCRIPTION
 Returns the last node of the list.

PARAMETERS
 - lst: The beginning of the list.

RETURN VALUE
 - Pointer to the last node of the list
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
