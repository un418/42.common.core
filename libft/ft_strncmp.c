/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:15:27 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/17 17:14:06 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
strncmp - compare two strings

SYNOPSIS
int strncmp(const char *s1, const char *s2, size_t n);

DESCRIPTION
The strcmp() function compares the two strings s1 and s2.
The locale is not taken into account.
The comparison is done using unsigned characters.

strcmp() returns an integer indicating the result of the comparison, as follows:

• 0, if the s1 and s2 are equal;
• a negative value if s1 is less than s2;
• a positive value if s1 is greater than s2.

The strncmp() function is similar,
except it compares only the first (at most) n bytes of s1 and s2.

RETURN VALUE
The strcmp() and strncmp() functions return an integer less than, equal to,
or greater than zero if s1 (or the first n bytes thereof) is  found,
respectively, to be less than, to match, or be greater than s2.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (((unsigned char)*s1 || (unsigned char)*s2) && n--)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
