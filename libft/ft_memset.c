/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:07:19 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:35:37 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_memset() – fill a byte string with a byte value

DESCRIPTION
 The ft_memset() function writes n bytes of value c (converted to unsigned char)
  to the string s.

RETURN VALUE
 The ft_memset() function returns the original value of s.
*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n --)
		*ptr++ = (unsigned char)c;
	return (s);
}
