/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:22:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:39:26 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_strdup() - save a copy of a string

DESCRIPTION
 The ft_strdup() function allocates sufficient memory for a copy
  of the string str, does the copy, and returns a pointer to it.
  The memory  is allocated  with malloc(3) and should be released with free(3)
  when no longer needed.

RETURN VALUE
 - On success returns a pointer to the copied string.
 - Return NULL if memory allocation fails
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p_dup;
	size_t	len_s;

	len_s = ft_strlen(s);
	p_dup = malloc((len_s + 1) * sizeof(char));
	if (!p_dup)
		return (NULL);
	ft_strlcpy(p_dup, s, len_s + 1);
	return (p_dup);
}
