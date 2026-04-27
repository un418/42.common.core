/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 01:24:32 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/26 01:38:41 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_lstdelone - 

DESCRIPTION 
 Takes a node as parameter and frees its content using the function ’del’.
 Free the node itself but does NOT free the next node.
PARAMETERS
 - lst: The node to free.
 - del: The address of the function used to delete the content.
RETURN VALUE
 None
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
