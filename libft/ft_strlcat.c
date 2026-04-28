/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:50:50 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 20:46:42 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_strlcat – size-bounded string concatenation

DESCRIPTION
The ft_strlcat() functions concatenate strings.
Designed to be safer, more consistent, and less error prone replacements
 for the easily misused functions strncpy(3) and strncat(3).

ft_strlcat() take the full size of the destination buffer
and guarantee NUL-termination if there is room.
Note that room for the NUL should be included in dstsize.
Also note that ft_strlcat() only operate on true ''C'' strings.
This means that both src and dst() must be NUL-terminated.

ft_strlcat() appends string src to the end of dst.
It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the result.
It will then NUL-terminate, unless dstsize is 0 or the original dst string was
longer than dstsize (in practice this should not happen as it means
that either dstsize is incorrect or that dst is not a proper string).

If the src and dst strings overlap, the behavior is undefined.

RETURN VALUES
 - The total length of the string it tried to create,
   means the initial length of dst plus the length of src.
 - If the return value is >= dstsize, the output string has been truncated.
   It is the caller's responsibility to handle this.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;

	len_dst = ft_strlen(dst);
	if (len_dst >= dstsize)
		return (dstsize + ft_strlen(src));
	else
	{
		ft_strlcpy(dst + len_dst, src, dstsize - len_dst);
		return (len_dst + ft_strlen(src));
	}
}
