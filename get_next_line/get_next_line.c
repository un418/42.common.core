/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:56 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/09 01:27:47 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// for debug
#include <stdio.h>


char	*get_next_line(int fd)
{
	char	delimiter;
	char	buf[BUFFER_SIZE + 1];
	int		n_read;
	static char	*stash; // no need to init static var set to null by default
	char	*match;
	char	*newstash;
	char	*line;
	
	delimiter = DELIMITER;
	match = NULL;
	line = "\0"; // /!\ should be null here ?  Or at least it is in stack
	buf[BUFFER_SIZE] = '\0';
	
	while (!match)
	{
		// feed buffer
		n_read = read(fd, buf, BUFFER_SIZE);
		// printf ("debug: buf :%s\n",buf); // debug
		if (n_read < 0)
		return (NULL);
		// store buffer to stash
		if (!stash) // manage the case of first start
			stash = ft_strdup("");
		// exit if file readed & last line proceed - need to be here to avoid init / race condition
		if (n_read == 0 && *stash == 0)
			return NULL;
		// printf ("debug: stashed :%s\n",stash); // debug

		newstash = ft_strjoin(stash,(const char *)buf);
		// printf ("debug: newtash :%s\n",newstash); // debug
		if (!newstash)
			return (NULL);
		free(stash);
		stash = ft_strdup(newstash);
		// printf ("debug: stash :%s\n",stash); // debug
		free(newstash);

		match = ft_strnchr(buf, DELIMITER, BUFFER_SIZE);
	}
	//loop exit mean - has been match

	//prepare line to return - need to stop at delim
	line = ft_line_from_stash(stash, delimiter); // stop at delim
	// printf ("debug: line :%s\n",line); //debug

	// clean buffer
	//store what stay after match in the buffer elsewere
	newstash = ft_gnl_substr((const char *)buf, delimiter, BUFFER_SIZE); // /!\ to improve -> not sure buffer size needed here
	free(stash);
	stash = ft_strdup(newstash);
	free(newstash);

	// free stach on exit 
	// 	free (stash);
	
	return (line);
}
