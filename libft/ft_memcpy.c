/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:16:22 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 23:03:28 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_memcpy - copy memory area

DESCRIPTION
 The ft_memcpy() function copies n bytes from memory area src
  to memory area dest.
 If dst and src overlap, behavior is undefined.
 Use memmove(3) if the memory areas do overlap.

RETURN VALUE
 - The original value of dest.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	const unsigned char	*p_src;

	p_dest = (unsigned char *)dest;
	p_src = (const unsigned char *)src;
	while (n--)
		*p_dest++ = *p_src++;
	return (dest);
}
