/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 00:00:00 by adaferna          #+#    #+#             */
/*   Updated: 2026/06/18 00:00:00 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Error-path tests for get_next_line: invalid / unreadable file descriptors.
   Kept apart from the nominal tests because they produce no comparable output
   (no reference file for diff_test.sh) and they print expected errno messages. */

#include "get_next_line.h"

// for printf
#include <stdio.h>

// for open()
#include <sys/types.h>
#include <fcntl.h>

// for dup() / dup2() / close()
#include <unistd.h>

// To get better error return
#include <errno.h>
#include <string.h>

/* Standard Colors */
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define RESET   "\033[0m"

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0); // disable printf buffer

	printf("\n______GET_NEXT_LINE_ERROR_TEST______\n\n");
	printf("BUFFER_SIZE = %d\n\n", BUFFER_SIZE);

	// arbitrary invalid file descriptor (never opened) -> must return NULL
	if (1)
	{
		int bad_fd = 42;
		printf("-- Test : arbitrary invalid fd (%d)\n\n", bad_fd);
		char *line = get_next_line(bad_fd);
		printf("get_next_line(%d) -> %p\n", bad_fd, (void *)line);
		if (line == NULL)
			printf(GREEN "PASS: returned NULL" RESET "\n");
		else
			printf(RED "FAIL: expected NULL" RESET "\n");
		free(line);
		printf("\n\n");
	}

	// test_file_dont_exist.txt -> open fails, get_next_line must return NULL
	if (1)
	{
		char *file="test_file_dont_exist.txt";
		printf("-- Test : %s\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d (errno=%d: %s)\n", fd, errno, strerror(errno));
		char *line = get_next_line(fd);
		printf("get_next_line(%d) -> %p\n", fd, (void *)line);
		if (line == NULL)
			printf(GREEN "PASS: returned NULL" RESET "\n");
		else
			printf(RED "FAIL: expected NULL" RESET "\n");
		free(line);
		if (fd >= 0)
			close(fd);
		printf("\n\n");
	}

	// test_no_access_file.txt -> open fails (no read permission), must return NULL
	// the Makefile errtest target creates this file with chmod 000 before running
	if (1)
	{
		char *file="test_no_access_file.txt";
		printf("-- Test : %s\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d (errno=%d: %s)\n", fd, errno, strerror(errno));
		char *line = get_next_line(fd);
		printf("get_next_line(%d) -> %p\n", fd, (void *)line);
		if (line == NULL)
			printf(GREEN "PASS: returned NULL" RESET "\n");
		else
			printf(RED "FAIL: expected NULL" RESET "\n");
		free(line);
		if (fd >= 0)
			close(fd);
		printf("\n\n");
	}

	// error in the middle of a read, then recover on the SAME fd
	if (1)
	{
		char *file="test0.txt";
		printf("-- Test : error mid-read then recover on the same fd (%s)\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d\n", fd);

		// 1) first valid call: read one line
		char *line = get_next_line(fd);
		printf("read #1 (valid)     -> %s", line ? line : "(null)\n");
		free(line);

		// 2) break the same fd: keep a copy of the open file (offset preserved),
		//    then close fd so this call reads from an invalid descriptor -> error
		int saved = dup(fd);
		close(fd);
		line = get_next_line(fd);
		printf("read #2 (error)     -> %s", line ? line : "(null)\n");
		if (line == NULL)
			printf(GREEN "PASS: error call returned NULL" RESET "\n");
		else
			printf(RED "FAIL: expected NULL on the broken fd" RESET "\n");
		free(line);

		// 3) restore the same fd number to the saved open file, then read again
		dup2(saved, fd);
		close(saved);
		line = get_next_line(fd);
		printf("read #3 (recovered) -> %s", line ? line : "(null)\n");
		free(line);

		close(fd);
		printf("\n\n");
	}
	return (0);
}
