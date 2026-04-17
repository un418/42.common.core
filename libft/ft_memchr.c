/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:20:27 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/17 18:13:58 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
memchr - scan memory for a character

SYNOPSIS
void *memchr(const void *s, int c, size_t n);

DESCRIPTION
The  memchr()  function scans the initial n bytes of the memory area
pointed to by s for the first instance of c.
Both c and the bytes of the memory area pointed to by s
are interpreted as unsigned char.

RETURN VALUE
The memchr() functions return a pointer to the matching byte
or NULL if the character does not occur in the given memory area.
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
