/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:56 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/09 23:35:50 by adaferna         ###   ########.fr       */
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
	static	char	*stash; // no need to init static var set to null by default
	static	int	file_end;
	char	*match;
	char	*newstash;
	static char	*line;
	
	delimiter = DELIMITER;
	match = NULL;
	newstash = NULL;
	line = NULL; // /!\ should be null here ?  Or at least it is in stack

	if (!stash) // manage the case of first start
		stash = ft_strdup("");
	
	if (file_end)
	{
		delimiter = '\0';
		if (!*stash)
			return (NULL);
	}
	// exit if file readed & last line proceed - need to be here to avoid init / race condition
	if (file_end && *stash == 0)
	{
		// free (stash); free(newstash);
		return NULL;

	}
	
	while (match = ft_strnchr(stash, DELIMITER, ft_strlen(stash), file_end), !match && !file_end)
	{
		// feed buffer
		n_read = read(fd, buf, BUFFER_SIZE);
		buf[n_read] = '\0';
		// printf ("debug: buf :%s\n",buf); // debug
		if (n_read < 0)
			return (NULL);
		// keep state of file readed for next run
		if (n_read == 0)
			file_end = 1;


		// printf ("debug: stashed :%s\n",stash); // debug


		// store buffer to stash
		if (!file_end) //
		{
			newstash = ft_strjoin(stash,(const char *)buf);
			// printf ("debug: newtash :%s\n",newstash); // debug
			free(stash);
			stash = ft_strdup(newstash);
			// printf ("debug: stash :%s\n",stash); // debug
			free(newstash);
		}
	}
	//loop exit mean - has been match
	
	if (*stash)
	{
		//prepare line to return - need to stop at delim
		line = ft_line_from_stash(stash, delimiter); // stop at delim
		// printf ("debug: line :%s\n",line); //debug
		
		// clean buffer
		//store what stay after match in the buffer elsewere
		newstash = ft_gnl_substr(stash, delimiter, ft_strlen(stash));
		free(stash);
		stash = ft_strdup(newstash);
		free(newstash);
	}

	return (line);
}
