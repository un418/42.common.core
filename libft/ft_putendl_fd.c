/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:14:17 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/22 18:21:32 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
ft_putendl_fd() - Output string to file descriptor followed by newline

DESCRIPTION
Outputs the string ’s’ to the specified file
descriptor followed by a newline.

PARAMETERS
- s: The string to output.
- fd: The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
