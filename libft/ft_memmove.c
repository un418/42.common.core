/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:57:51 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/16 15:48:56 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
memmove - copy memory area

SYNOPSIS
#include <string.h>
void *memmove(void *dest, const void *src, size_t n);

DESCRIPTION
The memmove()function copies n bytes from memory area src to memory area dest.
The memory areas may overlap:
copying takes place as though the bytes in src are first
copied into a temporary array that does not overlap src or dest,
and the bytes are then copied from the temporary array to dest.

RETURN VALUE
The memmove() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;

	p_dest = (char *)dest;
	p_src = (char *)src;
	if (dest == src)
		return (dest);
	else if (src > dest)
		while (n--)
			*p_dest++ = *p_src++;
	else if (dest > src)
	{
		p_dest += n - 1;
		p_src += n - 1;
		while (n--)
			*p_dest-- = *p_src--;
	}
	return (dest);
}
