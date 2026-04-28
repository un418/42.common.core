/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:06:10 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:45:41 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_isascii() - checks for a ASCII character

DESCRIPTION
 Checks whether c is a 7-bit unsigned char value
  that fits into the ASCII character set.

RETURN VALUE
 - 0 if test fail
 - non-zero if test pass
*/

#include "libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	else
		return (0);
}
