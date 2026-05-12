/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:56 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/12 03:58:41 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buf_to_stash(int fd, char *stash)
{
	char		buf[BUFFER_SIZE + 1];
	ssize_t		n_read;
	char		*newstash;

	while (!ft_strchr(stash, DELIMITER))
	{
		n_read = read(fd, buf, BUFFER_SIZE);
		if (n_read < 0)
			return (free(stash), stash = NULL, NULL);
		buf[n_read] = '\0';
		if (n_read == 0)
			return (stash);
		if (n_read > 0)
		{
			if (!stash)
				stash = ft_strjoin("", "");
			newstash = ft_strjoin(stash, buf);
			free (stash);
			stash = newstash;
		}
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	line = NULL;
	stash = buf_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	if (*stash)
	{
		line = ft_line_from_stash(stash, DELIMITER);
		stash = ft_clean_stash(stash, DELIMITER);
	}
	if (!line)
		return (free(stash), stash = NULL, NULL);
	return (line);
}
