/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:51:35 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/12 20:58:37 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// for printf
#include <stdio.h>

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

//to convert MACRO INT TO STR
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// function to compare to result and pretty print the result to tdout
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
	// int test_all = 1;
	// int itest = 1;
	// int fail = 0;
	// char err_msg[100]; 
	// int debug = 1;

	printf("\n______GET_NEXT_LINE_TEST______\n\n");
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	printf("DELIMITER = %c\n\n", DELIMITER);
	

	if (1)
	{
		// Define input file
		char *file="test0.txt";
		printf("-- Test : %s\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[60]; strcpy(output_file, file); strcat(output_file, "."); strcat(output_file, STR(BUFFER_SIZE)); strcat(output_file, ".output");
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
	if (0)
	{
		// Define input file
		char *file="test_empty_file.txt";
		printf("-- Test : %s\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[60]; strcpy(output_file, file); strcat(output_file, "."); strcat(output_file, STR(BUFFER_SIZE)); strcat(output_file, ".output");
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

	if (1)
	{
		// Define input file
		char *file="test_file_dont_exist.txt";
		printf("-- Test : %s\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[60]; strcpy(output_file, file); strcat(output_file, "."); strcat(output_file, STR(BUFFER_SIZE)); strcat(output_file, ".output");
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
		printf("\n\n");	}

	if (1)
	{
		// Define input file
		char *file="test_empty_file.txt";
		printf("-- Test : %s\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[60]; strcpy(output_file, file); strcat(output_file, "."); strcat(output_file, STR(BUFFER_SIZE)); strcat(output_file, ".output");
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

	if (1)
	{
		// Define input file
		char *file="test_one_line.txt";
		printf("-- Test : %s\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[60]; strcpy(output_file, file); strcat(output_file, "."); strcat(output_file, STR(BUFFER_SIZE)); strcat(output_file, ".output");
		int fd_out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error // Print & Don't exit on error // Print & Don't exit on error

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
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error // Print & Don't exit on error
		close(fd); close(fd_out);
		printf("\n\n");
	}
	
	if (1)
	{

		// Define input file
		char *file="test_only_nl.txt";
		printf("-- Test : %s\n\n", file);
		int fd = open(file, O_RDONLY);
		printf("fd = %d\n",fd);

		// Create output file
		char output_file[60]; strcpy(output_file, file); strcat(output_file, "."); strcat(output_file, STR(BUFFER_SIZE)); strcat(output_file, ".output");
		int fd_out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error // Print & Don't exit on error // Print & Don't exit on error

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
			{ fprintf( stderr, "Error is %s (errno=%d)\n", strerror( errno ), errno );} // Print & Don't exit on error // Print & Don't exit on error // Print & Don't exit on error
		close(fd); close(fd_out);
		printf("\n\n");
	}
	return (0);
}