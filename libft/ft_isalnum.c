/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:59:09 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 18:02:21 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_isalnum() - Checks for an alphanumeric character
DESCRIPTION
 Checks for an alphanumeric character;
 It is equivalent to (isalpha(c) || isdigit(c)).
IMPLEMENTATION NOTES
 Deliberatly choose to not call ft_isalpha and ft_isdigit and duplicate code
 Because I want my libft efficient
  and avoid the overhead cost of calling two external fonction at every test.
RETURN VALUE
 - 0 if test fail
 - non-zero if test pass
*/

#include "libft.h"

int	ft_isalnum(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')
		|| ('0' <= c && c <= '9'))
		return (1);
	else
		return (0);
}
