/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:53:21 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/22 18:00:59 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
DESCRIPTION
Outputs the character ’c’ to the specified file
descriptor.
*/

#include "libft.h"

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c , 1);
}
