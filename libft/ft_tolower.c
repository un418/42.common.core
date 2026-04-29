/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:26:51 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:44:00 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
 ft_tolower() - convert to lowercase

DESCRIPTION
 This function convert uppercase letters to lowercase.

 If c  is a uppercase letter, ft_tolower() returns its lowercase equivalent,
 Otherwise, it returns c.
 If c is neither an unsigned char value nor EOF,
  the behavior of these functions is undefined.

RETURN VALUE
- The converted letter, or c if the conversion was not possible.
*/

#include "libft.h"

static int	ft_isupper(int c)
{
	if (65 <= c && c <= 90)
		return (1);
	else
		return (0);
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}
