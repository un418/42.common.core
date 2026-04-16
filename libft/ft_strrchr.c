/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:44:16 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/16 21:06:05 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
strchr - locate last occurrence of the character in string

SYNOPSIS

char *strrchr(const char *s, int c);


DESCRIPTION
The strrchr() function returns a pointer 
to the last occurrence of the character c in the string s.

Here "character" means "byte";
these functions do not work with wide or multibyte characters.

RETURN VALUE
The  strrchr()functions return a pointer to the matched character
or NULL if the character is not found.
The terminating null byte is considered part of the string,
so that if c is specified as '\0',
these functions re‐turn a pointer to the terminator.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*end_s;

	end_s = s + ft_strlen(s);
	if (c == 0)
		return ((char *)end_s);
	else
		end_s--;
	while (end_s >= s)
	{
		if (*end_s == c)
			return ((char *)end_s);
		end_s--;
	}
	return (NULL);
}