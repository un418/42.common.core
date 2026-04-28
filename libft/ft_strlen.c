/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:30:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 21:11:52 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_strlen() - calculate the length of a string

DESCRIPTION
 The ft_strlen() function calculates the length of the string pointed to by s,
  excluding the terminating null byte ('\0').

RETURN VALUE
 - The number of characters that precede the terminating NUL character
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
