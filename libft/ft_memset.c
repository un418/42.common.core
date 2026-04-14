/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:07:19 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/14 17:26:06 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
SYNOPSIS
#include <string.h>

void *memset(void *s, int c, size_t n);

DESCRIPTION
The memset() function fills the first n bytes of the memory area
pointed to by s with the constant byte c.

RETURN VALUE
The memset() function returns a pointer to the memory area s.
*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		n--;
	}
	return (s);
}
