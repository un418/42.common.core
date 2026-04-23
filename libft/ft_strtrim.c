/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:53:44 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/23 17:34:01 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_strtrim() - trim prefix and suffix characters from a string.

PARAMETERS
- s1: The string to be trimmed.
- set: The string containing the set of characters to be removed.

RETURN VALUE
- The trimmed string.
- NULL if the allocation fails.

DESCRIPTION
Allocates memory (using malloc(3)) and returns a copy of ’s1’
 with characters from ’set’ removed  from the beginning and the end.
*/

#include "libft.h"

// helper boolean function to check if a character is in a list of character.
static int	ft_is_c_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p_start;
	char	*p_end;

	p_start = (char *)s1;
	p_end = ft_strrchr(s1, '\0') - 1;
	while (ft_is_c_in_set(*p_start, (char *)set) && *p_start)
		p_start++;
	while (ft_is_c_in_set(*p_end, (char *)set) && p_end > p_start)
		p_end--;
	return (ft_substr(s1, p_start - s1, p_end - p_start + 1));
}
