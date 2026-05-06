/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:46:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/06 14:56:44 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *str, ...);

size_t	ft_write_fd_char(int c, int fd);
size_t	ft_write_fd_str(char *s, int fd);

size_t	ft_writeunbr_fd_recurse(unsigned long ul, int fd);
size_t	ft_writenbr_fd(long n, int fd);
size_t ft_printf_int(va_list args);
size_t	ft_writehex_fd_recurse(unsigned long un, int fd, int upper);
size_t ft_printf_pointer(void *p);

#endif