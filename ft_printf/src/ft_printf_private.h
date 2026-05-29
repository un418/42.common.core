/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_private.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/29 00:00:00 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_PRIVATE_H
# define FT_PRINTF_PRIVATE_H

# include <unistd.h>

ssize_t	ft_write_fd_char(int c, int fd);
ssize_t	ft_write_fd_str(char *s, int fd);
ssize_t	ft_writesnbr_fd(long n, int fd);
ssize_t	ft_writeunbr_fd_recurse(unsigned long ul, int fd);
ssize_t	ft_writehex_fd_recurse(unsigned long un, int fd, int upper);
ssize_t	ft_write_fd_pointer(void *p, int fd);

#endif
