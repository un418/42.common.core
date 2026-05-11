/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:56 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/12 00:54:05 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// for debug
#include <stdio.h>

char	*buf_to_stash(int fd, char *stash)
{
	static char buf[BUFFER_SIZE + 1];
	ssize_t n_read;
	char *newstash;

	n_read = read(fd, buf, BUFFER_SIZE);
	if (n_read < 0)
		return (free(stash), stash = NULL, NULL);
	buf[n_read] = '\0';
	if (n_read > 0)
	{
		if (!stash)
			stash = ft_strjoin("","");
		newstash = ft_strjoin(stash, buf);
		free(stash);
		stash = newstash;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash; // no need to init static var set to null by default
	char		*match;
	char		*line;
	
	line = NULL; // /!\ should be null here ?  Or at least it is in stack
	match = NULL;

	// if (!stash) // manage the case of first start
	// 	stash = "";
	
	while (!match)
	{
		stash = buf_to_stash(fd ,stash);
		if (!stash)
		return (NULL);
		match = ft_strchr(stash, DELIMITER);
	}

	if (*stash)
	{
		line = ft_line_from_stash(stash, DELIMITER);
		stash = ft_clean_stash(stash, DELIMITER);
	}
	// exit condition
	if ((!line && !*stash) || !stash) // can be else
		return (free(stash), stash = NULL, NULL);
	
	return (line);
}
