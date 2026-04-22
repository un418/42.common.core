/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:44:16 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/22 17:41:56 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
strchr - locate first occurrence of the character in string

SYNOPSIS

char *strchr(const char *s, int c);


DESCRIPTION
The strchr() function returns a pointer 
to the first occurrence of the character c in the string s.

Here "character" means "byte";
these functions do not work with wide or multibyte characters.

RETURN VALUE
The  strchr()functions return a pointer to the matched character
or NULL if the character is not found.
The terminating null byte is considered part of the string,
so that if c is specified as '\0',
these functions re‐turn a pointer to the terminator.
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;

	cc = (char)c;
	while (*s)
	{
		if (*s == cc)
			return ((char *)s);
		s++;
	}
	if (cc == 0)
		return ((char *)s);
	else
		return (NULL);
}
