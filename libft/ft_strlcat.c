/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:50:50 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/22 00:36:13 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
strlcat – size-bounded string concatenation


SYNOPSIS
size_t  strlcat(char *dst, const char *src, size_t size);

DESCRIPTION
The strlcat() functions concatenate strings.
Designed to be safer, more consistent, and less error prone replacements
for the easily misused functions strncpy(3) and strncat(3).

strlcat() take the full size of the destination buffer
and guarantee NUL-termination if there is room.
Note that room for the NUL should be included in dstsize.
Also note that strlcat() only operate on true ''C'' strings.
This means that for strlcat() both src and dst() must be NUL-terminated.

strlcat() appends string src to the end of dst.
It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the result.
It will then NUL-terminate, unless dstsize is 0 or the original dst string was
longer than dstsize (in practice this should not happen as it means
that either dstsize is incorrect or that dst is not a proper string).

If the src and dst strings overlap, the behavior is undefined.

RETURN VALUES
strlcat() functions return the total length of the string it tried to create,
means the initial length of dst plus the length of src.

If the return value is >= dstsize, the output string has been truncated.
It is the caller's responsibility to handle this.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*p_dst;
	const char	*p_src;
	size_t		total;

	p_dst = dst;
	p_src = src;
	total = ft_strlen(p_dst) + ft_strlen(p_src);
	dstsize--;
	if (dstsize != 0)
	{
		while (dstsize-- && *dst)
			dst++;
		while (dstsize-- && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (total);
}
