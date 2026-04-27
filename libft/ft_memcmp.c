/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:30:02 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 00:52:05 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 memcmp - compare memory areas

DESCRIPTION
 The memcmp() function compares the first n bytes
  (each interpreted as unsigned char) of the memory areas s1 and s2.

RETURN VALUE
 - zero if the two strings are identical
 - Zero-length strings are always identical
 - otherwise returns the difference between the first two differing bytes
   (treated as unsigned char values, so that ‘\200’ is greater than ‘\0’, for example).
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*p_s1;
	const unsigned char		*p_s2;
	unsigned char			c1;
	unsigned char			c2;

	p_s1 = s1;
	p_s2 = s2;
	while (n--)
	{
		c1 = *p_s1;
		c2 = *p_s2;
		if (c1 != c2)
			return (c1 - c2);
		p_s1++;
		p_s2++;
	}
	return (0);
}
