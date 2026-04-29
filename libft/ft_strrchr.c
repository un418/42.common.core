/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:44:16 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:43:50 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_strrchr() - locate last occurrence of the character in string

DESCRIPTION
 The ft_strrchr() function locates the first occurrence of c
  (converted to a char) in the string pointed to by s.
 The terminating null character is considered part of the string,
  therefore if c is ‘\0’, the functions locate the terminating ‘\0’.

RETURN VALUE
 - Return a pointer to the last occurrence of the character
 - Return NULL if the character is not found
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p_end;

	p_end = s + ft_strlen(s);
	while (1)
	{
		if (*p_end == (char)c)
			return ((char *)p_end);
		if (p_end == s)
			return (NULL);
		p_end--;
	}
}
