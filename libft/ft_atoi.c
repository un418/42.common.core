/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:00:41 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 11:01:10 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_atoi – convert ASCII string to integer

DESCRIPTION
 The ft_atoi() function converts the initial portion of the string
 pointed by str to int representation.

IMPLEMENTATION NOTES
 - The string may begin with an arbitrary amount of white space 
  (as determined by isspace(3)) followed by a single optional ‘+’ or ‘-’ sign,
  stopping at the first character which is not a valid digit in the given base.
  - If the value cannot be represented as int (OVERFLOW),
    the behavior is UNDEFINED.

RETURN VALUE
 - Interger representation of the ASSCI string in input
*/

#include "libft.h"

// helper boolean function to check if the current caracter is a space
static int	ft_isspace(char c)
{
	if (c == 32 || (9 <= c && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	unsigned int	res;
	int				sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10;
		res = res + (*str - 48);
		str++;
	}
	return (sign * res);
}
