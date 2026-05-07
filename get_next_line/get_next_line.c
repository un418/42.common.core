/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:56 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/07 19:28:28 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	delimiter;
	char	*buf[BUFFER_SIZE];
	char	*line;
	int		n_read;

	delimiter = DELIMITER;
	line = "\0";
	//feed buffer
	n_read = read(fd, buf, BUFFER_SIZE);
	if (n_read > 0)
		return (NULL);

	// search delim in buffer
	char	*match;
	static char	*stash;
	// init stash to use strjoin only
	stash = malloc(1);
	*stash = 0;
	char	*newstash;
	match = ft_memchr(buf, DELIMITER, BUFFER_SIZE);
	while (!match)
	{
		// store buffer to stash
		newstash = ft_strjoin(stash,(const char *)buf);
		if (!newstash)
			return (NULL);
		free(stash);
		stash = newstash;
		free(newstash);
		// refeed buffer
		n_read = read(fd, buf, BUFFER_SIZE);
	}
	//has been match


	//prepare line to return

	line = ft_strjoin(line,stash);

	//store what stay after match in the buffer elsewere
	newstash = ft_gnl_substr((const char *)buf, delimiter, BUFFER_SIZE);
	free(stash);
	stash = newstash;
	free(newstash);


	return (line);
}
