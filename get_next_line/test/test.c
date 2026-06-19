/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:51:35 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/14 16:53:36 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// for printf
#include <stdio.h>

// for the teeprintf variadic helper (va_list / va_start / va_end)
#include <stdarg.h>

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

// function to compare to result and pretty print the result to stdout
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

// func to print in file and stdout at the same time
void teeprintf(int fd, const char *format, ...)
{
	// Init va && Print to stdout
	va_list args;	
	va_start(args, format);
	vprintf(format, args);
	va_end(args);	
	// Reintit va && Print to fd
	va_start(args, format);
	vdprintf(fd, format, args);
	va_end(args);
}


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0); // disable printf buffer
	mkdir("output", 0755); // make sure the output folder exists (ignored if already there)
	// int test_all = 1;
	// int itest = 1;
	// int fail = 0;
	// char err_msg[100]; 
	// int debug = 1;

	printf("\n______GET_NEXT_LINE_TEST______\n\n");
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	printf("DELIMITER = %c\n\n", DELIMITER);
	
	// test0.txt
	if (1)
	{
		// Define input file
		char *file="test0.txt";
		printf("-- Test : %s\n\n", file);
		char in_path[256]; snprintf(in_path, sizeof(in_path), "inputs/%s", file);
		int fd = open(in_path, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[256]; snprintf(output_file, sizeof(output_file), "output/%s.%d.output", file, BUFFER_SIZE);
		int fd_out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error

		char *line;
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			teeprintf(fd_out,"%s", line);
			free(line);
		}
		if (fd < 0)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error
		close(fd); close(fd_out);
		printf("\n\n");
	}

	// test_empty_file.txt
	if (1)
	{
		// Define input file
		char *file="test_empty_file.txt";
		printf("-- Test : %s\n\n", file);
		char in_path[256]; snprintf(in_path, sizeof(in_path), "inputs/%s", file);
		int fd = open(in_path, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[256]; snprintf(output_file, sizeof(output_file), "output/%s.%d.output", file, BUFFER_SIZE);
		int fd_out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error 

		char *line;
		line = get_next_line(fd);
		teeprintf(fd_out,"%s", line);
		free(line);
		if (fd < 0)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error
		close(fd); close(fd_out);
		printf("\n\n");	}

	// test_empty_file.txt
	if (1)
	{
		// Define input file
		char *file="test_empty_file.txt";
		printf("-- Test : %s\n\n", file);
		char in_path[256]; snprintf(in_path, sizeof(in_path), "inputs/%s", file);
		int fd = open(in_path, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[256]; snprintf(output_file, sizeof(output_file), "output/%s.%d.output", file, BUFFER_SIZE);
		int fd_out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error

		char *line;
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			teeprintf(fd_out,"%s", line);
			free(line);
		}
		if (fd < 0)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error
		close(fd); close(fd_out);
		printf("\n\n");
	}

	// test_one_line.txt
	if (1)
	{
		// Define input file
		char *file="test_one_line.txt";
		printf("-- Test : %s\n\n", file);
		char in_path[256]; snprintf(in_path, sizeof(in_path), "inputs/%s", file);
		int fd = open(in_path, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[256]; snprintf(output_file, sizeof(output_file), "output/%s.%d.output", file, BUFFER_SIZE);
		int fd_out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error
		char *line;
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			teeprintf(fd_out,"%s", line);
			free(line);
		}
		if (fd < 0)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error 
		close(fd); close(fd_out);
		printf("\n\n");
	}
	
	// test_only_nl.txt
	if (1)
	{

		// Define input file
		char *file="test_only_nl.txt";
		printf("-- Test : %s\n\n", file);
		char in_path[256]; snprintf(in_path, sizeof(in_path), "inputs/%s", file);
		int fd = open(in_path, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[256]; snprintf(output_file, sizeof(output_file), "output/%s.%d.output", file, BUFFER_SIZE);
		int fd_out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error

		char *line;
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			teeprintf(fd_out,"%s", line);
			free(line);
		}

		if (fd == -1)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error
		close(fd); close(fd_out);
		printf("\n\n");
	}
	return (0);
}