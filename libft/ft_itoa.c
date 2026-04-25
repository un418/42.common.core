/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 02:38:54 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/25 03:54:01 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_itoa() - Convert integer to string

PARAMETERS
- n: The integer to convert.

RETURN VALUE
- The string representing the integer.
- NULL if the allocation fails.

DESCRIPTION
Allocates memory (using malloc(3)) and returns a string representing the integer
 received as an argument.
Negative numbers are handled.
*/

#include "libft.h"

// helper function to get the size of the array
static int	ft_itoa_size(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	long	ln;
	int		size;
	char	sign;

	ln = n;
	sign = 0;
	size = ft_itoa_size(n);
	if (ln < 0)
	{
		size++;
		ln *= -1;
		sign = 1;
	}
	itoa = ft_calloc(size + 1, sizeof(char));
	if (!itoa)
		return (NULL);
	while (size--)
	{
		itoa[size] = (ln % 10) + '0';
		ln /= 10;
		if (sign && size == 0)
			itoa[size] = '-';
	}
	return (itoa);
}
