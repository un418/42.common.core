/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:26:53 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/14 18:32:34 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
SYNOPSIS
void bzero(void *s, size_t n);
DESCRIPTION
The bzero() function erases the data in the n bytes of the memory 
starting at the location pointed to by s,
by writing zeros (bytes containing '\0') to that area.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
