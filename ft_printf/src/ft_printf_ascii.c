/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:26:16 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/06 15:23:16 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_write_fd_char(int c, int fd)
{
	return (write(fd, &c, 1));
}

size_t	ft_write_fd_str(char *s, int fd)
{
	size_t	counter;

	counter = 0;
	if (!s)
		return (ft_write_fd_str("(null)", fd));
	while (*s)
	{
		write(fd, &*s++, 1);
		counter++;
	}
	return (counter);
}
