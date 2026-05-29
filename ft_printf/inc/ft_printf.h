/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:46:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/29 17:07:58 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# define FT_STDOUT		1
# define FT_STDERR		2

int	ft_printf(const char *str, ...);
int	ft_dprintf(int fd, const char *str, ...);
int	ft_vprintf(const char *str, va_list args);
int	ft_vdprintf(int fd, const char *str, va_list args);

#endif
