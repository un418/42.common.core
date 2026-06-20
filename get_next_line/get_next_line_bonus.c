/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:56 by adaferna          #+#    #+#             */
/*   Updated: 2026/06/20 00:15:30 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char		*stash[1048576];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1048575)
		return (NULL);
	line = NULL;
	stash[fd] = buf_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	if (*stash[fd])
		line = ft_line_from_stash(stash[fd], DELIMITER);
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	stash[fd] = ft_clean_stash(stash[fd], DELIMITER);
	return (line);
}

/* 
#include <fcntl.h>
#include <stdio.h>
int main(void)
{
    int   fd1 = open("file1.txt", O_RDONLY);
    int   fd2 = open("file2.txt", O_RDONLY);
    int   fd3 = open("file3.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd1)) != NULL)
    {
        printf("fd1: %s", line);
        free(line);
        line = get_next_line(fd2);
        printf("fd2: %s", line);
        free(line);
        line = get_next_line(fd3);
        printf("fd3: %s", line);
        free(line);
    }
    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
 */
