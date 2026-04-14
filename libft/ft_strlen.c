/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:30:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/14 15:37:29 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
DESCRIPTION
The strlen() function calculates the length of the string pointed to by s,
excluding the terminating null byte ('\0').
RETURN VALUE
The strlen() function returns the number of bytes in the string pointed to by s.
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
