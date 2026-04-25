/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:44:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/25 16:16:50 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_lstnew - create a new node of struct s_list (alias t_list)

DESCRIPTION
 Allocates memory (using malloc(3)) and returns a new node.
 The ’content’ member variable is initialized with the given parameter ’content’.
 The variable ’next’ is initialized to NULL.
PARAMETERS
 - content: The content to store in the new node.
RETURN VALUE
 - pointer to the new node
*/

// Don't fail if &content = NULL allows the capability to create node without content
// Is it really usefull or should I fail at this point ?

#include "libft.h"

t_list  *ft_lstnew(void *content)
{
	t_list *node;

	node = ft_calloc(1, sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
