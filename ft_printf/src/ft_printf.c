/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:56:29 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/29 20:59:27 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_private.h"
#include "ft_printf.h"

static ssize_t	ft_dprintf_switch(int fd, va_list args, const char *str)
{
	if (*str == 'c')
		return (ft_write_fd_char(va_arg(args, int), fd));
	else if (*str == '%')
		return (ft_write_fd_char('%', fd));
	else if (*str == 's')
		return (ft_write_fd_str(va_arg(args, char *), fd));
	else if (*str == 'd' || *str == 'i')
		return (ft_writesnbr_fd(va_arg(args, int), fd));
	else if (*str == 'u')
		return (ft_writeunbr_fd_recurse(va_arg(args, unsigned int), fd));
	else if (*str == 'x')
		return (ft_writehex_fd_recurse(va_arg(args, unsigned int), fd, 0));
	else if (*str == 'X')
		return (ft_writehex_fd_recurse(va_arg(args, unsigned int), fd, 1));
	else if (*str == 'p')
		return (ft_write_fd_pointer(va_arg(args, void *), fd));
	else if (*str == '\0')
		return (-1);
	else
		return (ft_write_fd_char('%', fd) + ft_write_fd_char(*str, fd));
}

int	ft_vdprintf(int fd, const char *str, va_list args)
{
	ssize_t	count;
	ssize_t	ret;

	count = 0;
	ret = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ret = ft_dprintf_switch(fd, args, str);
			if (ret == -1)
				return (-1);
			count += ret;
			if (*str)
				str++;
			continue ;
		}
		ret = ft_write_fd_char(*str, fd);
		if (ret == -1)
			return (-1);
		count += ret;
		str++;
	}
	return (count);
}

int	ft_vprintf(const char *str, va_list args)
{
	return (ft_vdprintf(FT_STDOUT, str, args));
}

int	ft_dprintf(int fd, const char *str, ...)
{
	ssize_t	count;
	va_list	args;

	count = 0;
	va_start(args, str);
	count = ft_vdprintf(fd, str, args);
	va_end(args);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	ssize_t	count;
	va_list	args;

	count = 0;
	va_start(args, str);
	count = ft_vprintf(str, args);
	va_end(args);
	return (count);
}
