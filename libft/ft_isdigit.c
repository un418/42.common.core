/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:38:20 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:17:53 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_isdigit() - checks for a digit
DESCRIPTION
 Checks for a digit (0 through 9).
RETURN VALUE
 - 0 if test fail
 - non-zero if test pass
*/

#include "libft.h"

int	ft_isdigit(int c)
{
	if (('0' <= c && c <= '9'))
		return (1);
	else
		return (0);
}
