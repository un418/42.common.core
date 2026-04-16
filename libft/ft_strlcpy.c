/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:35:07 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/16 18:50:58 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
strlcpy — size-bounded string copying and concatenation

LIBRARY
Utility functions from BSD systems (libbsd, -lbsd)

SYNOPSIS
#include <string.h>
(See libbsd(7) for include usage.)

size_t strlcpy(char *dst, const char *src, size_t size);
DESCRIPTION
The strlcpy()functions copy strings.
Designed to be safer, more consistent,
and less error prone replacements for strncpy(3).
Unlike those functions, strlcpy() take the full size of the buffer
(not just the length) and guarantee to
NUL-terminate the result (as long as size is larger than 0.
Note that a byte for the NUL should be included in size.
Also note that strlcpy() only operate on true “C” strings.
This means that for strlcpy() src must be NUL-terminated.

The strlcpy() function copies up to size - 1 characters
from the NUL-terminated string src to dst, NUL-terminating the result.


RETURN VALUES
The strlcpy()functions return the total length
of the string they tried to create.
For strlcpy() that means the length of src.

While this may seem somewhat confusing,
it was done to make truncation detection simple.
*/

// 

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
