/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:57:51 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/15 17:11:59 by adaferna         ###   ########.fr       */
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
/* 
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	tmp;

	while (n--)
	{
		tmp = *(char *)src++;
		*(char *)dest++ = tmp;
	}
	return (dest);
} */

#include <stdio.h>
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	tmp[n+1];
	int		i;

	i = 0;
	while (i < (int)n)
		tmp[i++] = *(char *)src++;
	tmp[i] = 0;
	printf("tmp:%s\n",tmp);
	i = 0;
	while (i < (int)n)
		*(char *)dest++ = tmp[i++];
	return (dest);
}
