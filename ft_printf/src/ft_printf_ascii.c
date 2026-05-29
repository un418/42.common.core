/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:26:16 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/20 15:43:11 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_private.h"

ssize_t	ft_write_fd_char(int c, int fd)
{
	return (write(fd, &c, 1));
}

ssize_t	ft_write_fd_str(char *s, int fd)
{
	ssize_t	counter;
	ssize_t	ret;

	counter = 0;
	if (!s)
		return (ft_write_fd_str("(null)", fd));
	while (*s)
	{
		ret = write(fd, &*s++, 1);
		if (ret == -1)
			return (-1);
		counter++;
	}
	return (counter);
}
