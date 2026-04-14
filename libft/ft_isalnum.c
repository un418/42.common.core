/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:59:09 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/14 13:02:00 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
isalnum()
checks for an alphanumeric character;
it is equivalent to (isalpha(c) || isdigit(c)).
*/

// Deliberatly choose to not call ft_isalpha and ft_isdigit and duplicate code
// Because I want my libft efficient
// and avoid the overhead cost of calling two external fonction.

int	ft_isalnum(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')
		|| ('0' <= c && c <= '9'))
		return (1);
	else
		return (0);
}
