/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:26:51 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/16 19:32:14 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
tolower - convert lowercase

SYNOPSIS
int tolower(int c);

DESCRIPTION
This function convert uppercase  letters to lowercase.

If  c  is a uppercase letter, tolower() returns its lowercase equivalent,
if an lowercase representation exists in the current locale.
Otherwise, it returns c.

If c is neither an unsigned char value nor EOF,
the behavior of these functions is undefined.

RETURN VALUE
The value returned is that of the converted letter,
or c if the conversion was not possible.
*/

#include "libft.h"

static int	ft_islower(int c)
{
	if (65 <= c && c <= 90)
		return (1);
	else
		return (0);
}

int	ft_tolower(int c)
{
	if (ft_islower(c))
	{
		c += 32;
	}
	return (c);
}
