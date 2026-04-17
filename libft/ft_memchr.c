/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:20:27 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/17 18:06:58 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
memchr, memrchr, rawmemchr - scan memory for a character

SYNOPSIS
#include <string.h>

void *memchr(const void *s, int c, size_t n);
void *memrchr(const void *s, int c, size_t n);

DESCRIPTION
The  memchr()  function scans the initial n bytes of the memory area pointed to by s for the first instance of c.  Both c and the bytes of the memory
area pointed to by s are interpreted as unsigned char.

The memrchr() function is like the memchr() function, except that it searches backward from the end of the n bytes pointed to by s instead of forward
from the beginning.

The rawmemchr() function is similar to memchr(): it assumes (i.e., the programmer knows for certain) that an instance of c lies somewhere in the memory area starting at the location pointed to by s, and so performs an optimized search for c (i.e., no use of a count argument to limit the range  of the search).
If an instance of c is not found, the results are unpredictable.  The following call is a fast means of locating a string's terminating null byte:
char *p = rawmemchr(s, '\0');

RETURN VALUE
The memchr() and memrchr() functions return a pointer to the matching byte or NULL if the character does not occur in the given memory area.

The rawmemchr() function returns a pointer to the matching byte, if one is found.  If no matching byte is found, the result is unspecified.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*p_s;
	
	p_s = s;
	while (n--)
	{
		if (*p_s == (char)c)
			return ((void *)p_s);
		p_s++;
	}
	return (NULL);
}
