/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:00:41 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/21 19:46:07 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
atoi – convert ASCII string to integer

SYNOPSIS
int atoi(const char *str);

DESCRIPTION
The atoi() function converts the initial portion of the string
pointed by str to int representation.

It is equivalent to:
(int)strtol(str, (char **)NULL, 10);

IMPLEMENTATION NOTES
The atoi() and atoi_l() functions are thread-safe and async-cancel-safe.

strtol() - DESCRIPTION
The strtol() function converts the string in str to a long value.
The string may begin with an arbitrary amount of white space 
(as determined by isspace(3)) followed by a single optional ‘+’ or ‘-’ sign.
The remainder of the string is converted to a long, long long, intmax_t
or quad_t value in the obvious manner, stopping at the first character which
is not a valid digit in the given base.
*/

#include "libft.h"

// int	ft_isspace(char c)  // for testing
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
