/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:16:22 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 01:11:31 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 memcpy - copy memory area

DESCRIPTION
 The memcpy() function copies n bytes from memory area src to memory area dest.
 If dst and src overlap, behavior is undefined.
 Use memmove(3) if the memory areas do overlap.

RETURN VALUE
 The memcpy() function returns the original value of dst.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;

	ptr = dest;
	while (n--)
		*ptr++ = *(char *)src++;
	return (dest);
}
