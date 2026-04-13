/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:21:37 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/13 13:44:47 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_isalpha()

checks  for an alphabetic character;
in the standard "C" locale, it is equivalent to (isupper(c) || islower(c)).
In some locales, there may be  additional characters for which isalpha()
is true—letters which are neither uppercase nor lowercase.
*/

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1);
	else
		return (0);
}

/* 
#include <stdio.h>
int main(void)
{
	char *str = "ajQT09,.1-]\\~";
	while (*str)
	{
		printf("%c : %d\n",*str,ft_isalpha(*str));
		str++;
	}
}
 */
