/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:44:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:38:55 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_lstnew - create a new node of struct s_list (alias t_list)

DESCRIPTION
 Allocates memory (using malloc(3)) and returns a new node.
 The ’content’ member variable is initialized with the parameter ’content’.
 The variable ’next’ is initialized to NULL.

PARAMETERS
 - content: The content to store in the new node.

RETURN VALUE
 - Pointer to the new node
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
