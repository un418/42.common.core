/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:53:21 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/22 18:22:04 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ft_putchar_fd() - Output char to file descriptor

DESCRIPTION
Outputs the character ’c’ to the specified file
descriptor.

PARAMETERS
- c: The character to output.
- fd: The file descriptor on which to write
*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
