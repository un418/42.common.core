/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:13:04 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/23 11:31:25 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_strjoin() - Join two strings in a new one.

PARAMETERS
- s1: The prefix string.
- s2: The suffix string.
RETURN VALUE

The new string.
NULL if the allocation fails.

DESCRIPTION
Allocates memory (using malloc(3)) and returns a new string,
which is the result of concatenating ’s1’ and ’s2’.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p_join;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p_join = ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (!p_join)
		return (NULL);
	ft_strlcpy(p_join, s1, len_s1 + 1);
	ft_strlcat(p_join, s2, len_s1 + len_s2 +1);
	return (p_join);
}
