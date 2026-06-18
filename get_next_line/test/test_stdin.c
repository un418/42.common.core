/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 00:00:00 by adaferna          #+#    #+#             */
/*   Updated: 2026/06/18 00:00:00 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Interactive test: read lines from the standard input (fd 0) with
   get_next_line and echo them back. Stop with Ctrl-D (sends EOF). */

#include "get_next_line.h"

#include <stdio.h>   // printf
#include <stdlib.h>  // free
#include <unistd.h>  // STDIN_FILENO

int main(void)
{
	char *line;

	printf("Type lines and press Enter. Ctrl-D on an empty line to quit.\n\n");
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		printf("got -> %s", line);
		free(line);
	}
	printf("\nEOF reached, bye.\n");
	return (0);
}
