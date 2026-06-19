/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 00:00:00 by adaferna          #+#    #+#             */
/*   Updated: 2026/06/19 17:26:54 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Multi-fd bonus test ("Bonus part").
   Reads from several file descriptors in a round-robin fashion (fd a, fd b,
   fd c, then a, b, c again...) and checks that get_next_line never loses or
   mixes the reading state of one fd with another.

   Each channel's lines are echoed to stdout (with its fd label) AND appended,
   in arrival order, to output/<input>.bonus.output. If get_next_line keeps a
   clean per-fd state, each output file rebuilds its source input exactly:
   `make bonus` then diffs them byte-for-byte.
 */

#include "get_next_line_bonus.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/* Standard Colors */
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define RESET   "\033[0m"

// one read channel: an input, its open fd, the .output mirror, and "done" flag
typedef struct s_chan
{
	const char	*file;
	int			fd;
	int			fd_out;
	int			done;
}	t_chan;

// func to print in file and stdout at the same time
void teeprintf(int fd, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	va_start(args, format);
	vdprintf(fd, format, args);
	va_end(args);
}

// open a channel's input (read) and its output/<file>.bonus.output mirror (write)
void open_chan(t_chan *c)
{
	c->done = 0;
	char in_path[256]; snprintf(in_path, sizeof(in_path), "inputs/%s", c->file);
	c->fd = open(in_path, O_RDONLY);
	if (c->fd < 0)
	{
		fprintf(stderr, RED "open error on %s: %s" RESET "\n", c->file, strerror(errno));
		c->done = 1;
	}
	char out[256]; snprintf(out, sizeof(out), "output/%s.bonus.output", c->file);
	c->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (c->fd_out == -1)
		fprintf(stderr, "Error is %s (errno=%d)\n", strerror(errno), errno);
}

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	mkdir("output", 0755);

	printf("\n______GET_NEXT_LINE_BONUS_TEST (multi-fd)______\n\n");
	printf("BUFFER_SIZE = %d\n\n", BUFFER_SIZE);

	// three different inputs (distinct line lengths) so a mix-up would be obvious
	t_chan chans[3] = {
		{ "bonus_a.txt", -1, -1, 0 },
		{ "bonus_b.txt", -1, -1, 0 },
		{ "bonus_c.txt", -1, -1, 0 },
	};
	int n = 3;
	for (int i = 0; i < n; i++)
		open_chan(&chans[i]);

	// round-robin: one line per fd per round, until every fd hits EOF
	int remaining = n;
	while (remaining > 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (chans[i].done)
				continue ;
			char *line = get_next_line(chans[i].fd);
			if (!line)
			{
				chans[i].done = 1;
				remaining--;
				continue ;
			}
			printf("fd[%d] %-22s -> %s", chans[i].fd, chans[i].file, line);
			teeprintf(chans[i].fd_out, "%s", line);
			// keep stdout readable when a line has no trailing newline
			if (line[0] && line[strlen(line) - 1] != '\n')
				printf("\n");
			free(line);
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (chans[i].fd >= 0)
			close(chans[i].fd);
		if (chans[i].fd_out >= 0)
			close(chans[i].fd_out);
	}
	printf("\nAll fds drained. `make bonus` now diffs each .bonus.output against its source.\n\n");
	return (0);
}
