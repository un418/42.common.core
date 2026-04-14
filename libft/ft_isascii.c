/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:06:10 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/14 14:52:36 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
isascii()
checks whether c is a 7-bit unsigned char value
that fits into the ASCII character set.
*/

#include "libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	else
		return (0);
}
