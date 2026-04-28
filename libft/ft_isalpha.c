/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:21:37 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:49:04 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_isalpha() - Checks for an alphabetic character

DESCRIPTION
 Checks for an alphanumeric character.
 It is equivalent to (isupper(c) || islower(c))

IMPLEMENTATION NOTES
 Deliberatly choose to not call ft_isupper and ft_islower and duplicate code
 Because I want my libft efficient
  and avoid the overhead cost of calling two external fonction at every test.

RETURN VALUE
 - 0 if test fail
 - non-zero if test pass
*/

#include "libft.h"

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1);
	else
		return (0);
}
