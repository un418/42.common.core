/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:56 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/12 18:14:31 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	stash = buf_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	if (*stash)
		line = ft_line_from_stash(stash, DELIMITER);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = ft_clean_stash(stash, DELIMITER);
	return (line);
}
