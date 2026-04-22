/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:22:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/22 16:37:17 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
strdup - duplicate a string

SYNOPSIS
char *strdup(const char *s);

DESCRIPTION
The strdup() function returns a pointer to a new string
 which is a duplicate of the string s. 
Memory for the new string is obtained with malloc(3),
 and can be freed with free(3).

RETURN VALUE
On success, the strdup() function returns a pointer to the duplicated string.
It returns NULL if insufficient memory was available.

*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p_dup;

	p_dup = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (p_dup)
	{
		ft_strlcpy(p_dup, s, ft_strlen(s) + 1);
		return (p_dup);
	}
	else
		return (NULL);
}
