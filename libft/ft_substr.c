/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:55:16 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/22 21:04:46 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_substr() - Create a substring of `len` size.

PARAMETERS
- s: The original string from which to create the substring.
- start: The starting index of the substring within ’s’.
- len: The maximum length of the substring.
RETURN VALUE
The substring.
NULL if the allocation fails.

DESCRIPTION
Allocates memory (using malloc(3)) and returns a substring from the string ’s’.
The substring starts at index ’start’ and has a maximum length of ’len’.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p_sub;
	size_t	len_s;

	len_s = ft_strlen(s);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	p_sub = ft_calloc(len + 1, sizeof(char));
	if (!p_sub)
		return (NULL);
	ft_strlcpy(p_sub, (s + start), len + 1);
	return (p_sub);
}
