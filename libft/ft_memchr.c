/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:20:27 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 01:13:48 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 memchr - scan memory for a character

DESCRIPTION
 The memchr() function locates the first occurrence 
  of c (converted to an unsigned char) in string s.

RETURN VALUE
 The memchr() function returns a pointer to the byte located,
  or NULL if no such byte exists within n bytes.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p_s;

	p_s = s;
	while (n--)
	{
		if (*p_s == (unsigned char)c)
			return ((void *)p_s);
		p_s++;
	}
	return (NULL);
}
