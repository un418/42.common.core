/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:41:35 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/28 22:37:14 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_split() - Create substrings array from a string splited at delimiter

DESCRIPTION
 Allocates memory (using malloc(3)) and returns an array of strings
  obtained by splitting ’s’ using the character ’c’ as a delimiter.
 Each string in the returned array is allocated independently.
 The array of pointers itself is also allocated dynamically.
 The returned array must be NULL terminated.

PARAMERTES
- s: The string to be split.
- c: The delimiter character.

RETURN VALUE
 - The array of new strings resulting from the split.
 - NULL if any memory allocation fails.

MEMORY MANAGEMENT
 The returned structure will be released using:
  1) free() on each string in the array;
  2) free() the array itself.
*/

#include "libft.h"

// helper function to count the number of string to create.
static size_t	ft_split_count(const char *str, const char c)
{
	size_t	count;

	count = 0;
	while (1)
	{
		while (*str == c && *str)
			str++;
		if (!*str)
			return (count);
		while (*str != c && *str)
			str++;
		count++;
	}
}

// helper function to get lenght of splitted string
// - count lenght for str to delimiter `c` or end of string
static size_t	ft_split_len(const char *str, const char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

// helper function to free memory properly in case of error
// - free memory and set pointer to `NULL`
// - set pointer to `NULL` allow to retrieve error in case of trying to
//   read or write data in memory address that have been free earlier.
static void	*ft_split_free(char **split)
{
	while (*split)
	{
		free(*split);
		*split++ = NULL;
	}
	free(split);
	split = NULL;
	return (NULL);
}

// helper function to create substring
// - copy `src` to `dest` till delimiter or end of string
// - `NULL`-terminate in place of delimiter match
// - return `pointer` to last delimiter match
static char	*ft_split_extract_to(char *dst, const char *src, const char c)
{
	while (*src && *src != c)
		*dst++ = *src++;
	*dst = '\0';
	return ((char *)src);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	split = ft_calloc(ft_split_count(s, c) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			split[i] = malloc((ft_split_len(s, c)) + 1 * sizeof(char));
			if (!split[i])
				return (ft_split_free(split));
			s = ft_split_extract_to(split[i], s, c);
			i++;
		}
	}
	return (split);
}
