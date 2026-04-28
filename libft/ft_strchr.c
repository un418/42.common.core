/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:44:16 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 22:43:26 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_strchr - locate first occurrence of the character in string

DESCRIPTION
 The ft_strchr() function locates the first occurrence of c
  (converted to a char) in the string pointed to by s.
 The terminating null character is considered part of the string,
  therefore if c is ‘\0’, the functions locate the terminating ‘\0’.

RETURN VALUE
 - Return a pointer to the first occurrence of the character
 - Return NULL if the character is not found
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (*s == '\0')
			return (NULL);
		s++;
	}
}
