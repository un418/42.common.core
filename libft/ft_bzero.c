/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:26:53 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:41:23 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 bzero, explicit_bzero - zero a byte string

DESCRIPTION
 The bzero() function erases the data in the n bytes of the memory 
  starting at the location pointed to by s,
  by writing zeros (bytes containing '\0') to that area.

RETURN VALUE
 - None
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
