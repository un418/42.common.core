/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:57:51 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 23:06:39 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_memmove - copy memory area

DESCRIPTION
 The ft_memmove() function copies n bytes from memory area src
  to memory area dest.
 The two strings may overlap,
  the copy is always done in a non-destructive manner.

RETURN VALUE
 The ft_memmove() function returns the original value of dest.
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	const unsigned char	*p_src;

	p_dest = (unsigned char *)dest;
	p_src = (const unsigned char *)src;
	if (dest == src)
		return (dest);
	else if (src > dest)
		while (n--)
			*p_dest++ = *p_src++;
	else if (dest > src)
	{
		p_dest += n -1;
		p_src += n - 1;
		while (n--)
			*p_dest-- = *p_src--;
	}
	return (dest);
}
