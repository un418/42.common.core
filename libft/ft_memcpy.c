/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:16:22 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/15 12:55:11 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
memcpy - copy memory area

SYNOPSIS
include <string.h>
void *memcpy(void *dest, const void *src, size_t n);

DESCRIPTION
The memcpy() function copies n bytes from memory area src to memory area dest.
The memory areas must not overlap.
Use memmove(3) if the memory areas do overlap.

RETURN VALUE
The memcpy() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr;

	ptr = dest;
	while (n--)
		*ptr++ = *(char *)src++;
	return (dest);
}
