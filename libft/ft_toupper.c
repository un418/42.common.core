/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:45:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/16 19:23:22 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
toupper - convert uppercase

SYNOPSIS
int toupper(int c);

DESCRIPTION
This function convert lowercase letters to uppercase.

If  c  is a lowercase letter, toupper() returns its uppercase equivalent,
if an uppercase representation exists in the current locale.
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
	if (97 <= c && c <= 122)
		return (1);
	else
		return (0);
}

int	ft_toupper(int c)
{
	if (ft_islower(c))
	{
		c = c - 32;
	}
	return (c);
}
