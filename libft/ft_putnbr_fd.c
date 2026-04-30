/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:23:44 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/30 13:21:02 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_putnbr_fd() - Output number(s) to file descriptor

DESCRIPTION
 Outputs the integer ’n’ to the specified file descriptor.

PARAMETERS
 - n: The integer to output.
 - fd: The file descriptor on which to write
*/

#include "libft.h"

static void	ft_putnbr_fd_recurse(unsigned int un, int fd)
{
	if (un > 9)
		ft_putnbr_fd(un / 10, fd);
	ft_putchar_fd((un % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;

	ln = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ln = -n;
	}
	ft_putnbr_fd_recurse(ln, fd);
}
