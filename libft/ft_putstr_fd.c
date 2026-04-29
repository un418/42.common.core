/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:03:15 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:36:54 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_putendl_fd() - Output string to file descriptor NOT followed by newline

DESCRIPTION
 Outputs the string ’s’ to the specified file descriptor.

PARAMETERS
 - s: The string to output.
 - fd: The file descriptor on which to write
*/

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
