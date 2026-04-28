/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 13:20:02 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 21:20:12 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
 ft_strmapi() - Create a copy of a string by applying function f
  to each character of a string

DESCRIPTION
 Applies the function f to each character of the string s,
  passing its index as the first argument and the character as the second
 A new string is created (using malloc(3)) to store the results
  from the successive applications of f.
 Also note that ft_strmapi() only operate on true “C” strings.
 This means that for ft_strmapi() `*s` must be NUL-terminated.

PARAMETERS
 - s: The string to iterate over.
 - f: The function to apply to each character.


RETURN VALUE
 - The string created from the successive applications of ’f’.
 - Returns NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (NULL);
	i = 0;
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
