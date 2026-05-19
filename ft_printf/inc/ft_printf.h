/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:46:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/19 18:10:59 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

int		ft_printf(const char *str, ...);

ssize_t	ft_write_fd_char(int c, int fd);
ssize_t	ft_write_fd_str(char *s, int fd);

ssize_t	ft_writeunbr_fd_recurse(unsigned long ul, int fd);
ssize_t	ft_writesnbr_fd(long n, int fd);
ssize_t	ft_printf_int(va_list args);
ssize_t	ft_writehex_fd_recurse(unsigned long un, int fd, int upper);
ssize_t	ft_write_fd_pointer(void *p, int fd);

#endif