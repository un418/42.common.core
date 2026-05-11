/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:51:35 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/12 00:50:56 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// for printf
#include <stdio.h>
// for stings but not used
// #include <string.h>

// for open()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// To get better error return
#include <errno.h>
#include <string.h>

/* Standard Colors */
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define RESET   "\033[0m"

int ft_check(int check, int i, char *err_msg)
{
	if (check)
	{
		printf(GREEN); printf("TEST #%d PASS", i); printf(RESET);
		printf("\n\n\n");
		return (0);
	}
	else
	{
		printf(RED);
		printf("TEST #%d FAILED: ", i);
		printf(RESET);
		printf("%s\n\n\n", err_msg);
		return (1);
	}
}


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0); // disable printf buffer
	// int test_all = 1;
	// int itest = 1;
	// int fail = 0;
	// char err_msg[100]; 
	// int debug = 1;

	printf("\n______GET_NEXT_LINE_TEST______\n\n");
	printf("BUFFER_SIZE = %d\n\n", BUFFER_SIZE);
	

	int fd0;
	char *file0="test0.txt";
	fd0 = open(file0, O_RDONLY);
	if (fd0 < 0)
		{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno ); return (1); }

	char *line;
	while (1)
	{
		line = get_next_line(fd0);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd0);
	
/* 
	line = get_next_line(fd0);
	printf("%s", line);
	free(line);
 */
	return (0);

}