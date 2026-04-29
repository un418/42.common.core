/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:15:27 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:41:06 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_strncmp() - compare two strings

DESCRIPTION
 The ft_strncmp() function compares only the first n bytes of s1 and s2.
 The locale is not taken into account.
 The comparison is done using unsigned characters.

RETURN VALUE
 - 0, if the s1 and s2 are equal;
 - a negative value if s1 is less than s2;
 - a positive value if s1 is greater than s2.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
