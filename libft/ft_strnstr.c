/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:19:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:43:42 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_strnstr() — locate a substring in a string

DESCRIPTION
 The strnstr() function locates the first occurrence 
  of the null-terminated string little in the string big,
  where not more than len characters are searched.

 Characters that appear after a ‘\0’ character are not searched.
 Since the strnstr() function is a FreeBSD specific API, it should only be
  used when portability is not a concern.

RETURN VALUES
 - If little is an empty string, big is returned
 - If little occurs nowhere in big, NULL is returned
 - otherwise a pointer to the first character
    of the first occurrence of little is returned.

EXAMPLES
 The following sets the pointer ptr to NULL,
  because only the first 4 characters of largestring are searched:
  const char *largestring = "Foo Bar Baz";
  const char *smallstring = "Bar";
  char *ptr;
  ptr = strnstr(largestring, smallstring, 4);
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	size_t	len_big;

	len_little = ft_strlen(little);
	len_big = ft_strlen(big);
	if (*little == '\0')
		return ((char *)big);
	if (len_little > len_big)
		return (NULL);
	while (*big && len >= len_little)
	{
		if (*big == *little)
		{
			if (!ft_strncmp(big, little, len_little))
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
