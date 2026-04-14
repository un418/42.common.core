/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:20:54 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/14 14:52:27 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
isprint()
checks for any printable character including space.
*/

#include "libft.h"

int	ft_isprint(int c)
{
	if (32 <= c && c <= 126)
		return (1);
	else
		return (0);
}
