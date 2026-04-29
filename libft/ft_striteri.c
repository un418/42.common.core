/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:31:37 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:46:09 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_striteri() - Applies function to each character of a string

DESCRIPTION
 Applies the function ’f’ to each character of the string passed as argument,
  passing its index as the first argument.
 Each character is passed by address to ’f’ so it can be modified if necessary.
 Also note that ft_striteri() only operate on true “C” strings.
 This means that for ft_striteri() `*s` must be NUL-terminated.

 PARAMETERS
 - s: The string to iterate over.
 - f: The function to apply to each character.

 RETURN VALUE
 - None
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
