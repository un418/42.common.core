/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:19:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/17 21:18:18 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
strnstr — locate a substring in a string

LIBRARY
Utility functions from BSD systems (libbsd, -lbsd)

SYNOPSIS
char *strnstr(const char *big, const char *little, size_t len);

DESCRIPTION
The strnstr() function locates the first occurrence of the null-terminated string little in the string big,
where not more than len characters are searched.
Characters that appear after a ‘\0’ character are not searched.
Since the strnstr() function is a FreeBSD specific API, it should only be
used when portability is not a concern.

RETURN VALUES
If little is an empty string, big is returned; if little occurs nowhere in big, NULL is returned; otherwise a pointer to the first character of the
first occurrence of little is returned.

EXAMPLES
The following sets the pointer ptr to NULL, because only the first 4 characters of largestring are searched:

const char *largestring = "Foo Bar Baz";
const char *smallstring = "Bar";
char *ptr;

ptr = strnstr(largestring, smallstring, 4);
*/

#include "libft.h"

static char	*ft_strnchr(const char *s, int c, size_t len)
{
	while (*s && len--)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	else
		return (NULL);
}


char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*p_match;

	if (*little == '\0')
		return ((char *)big);
	while (*big)
	{
		p_match = ft_strnchr(big,*little,len);
		if (p_match)
		{
			big = p_match;
			if (!ft_memcmp(big, little, len))
			{
				return ((char *)big);
			}
			else
				big++;
		}
		else
			return (NULL);
	}
	return (NULL);
}
