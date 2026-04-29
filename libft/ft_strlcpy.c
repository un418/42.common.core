/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:35:07 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:40:49 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_strlcpy() — size-bounded string copying

DESCRIPTION
 The ft_strlcpy()functions copy strings.

 Designed to be safer, more consistent,
  and less error prone replacements for strncpy(3).
 Unlike this functions, ft_strlcpy() take the full size of the buffer
  (not just the length) and guarantee to
  NUL-terminate the result (as long as size is larger than 0.

 Note that a byte for the NUL should be included in size.
 Also note that ft_strlcpy() only operate on true “C” strings.
 This means that src must be NUL-terminated.

 The ft_strlcpy() function copies up to size - 1 characters
  from the NUL-terminated string src to dst, NUL-terminating the result.

RETURN VALUES
 - Return the total length of the string it tried to create. (length of src)
   It was done to make truncation detection simple.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*p_src;

	p_src = src;
	if (size != 0)
	{
		while (--size && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (ft_strlen(p_src));
}
