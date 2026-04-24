/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:41:35 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/24 15:02:23 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parameters
- s: The string to be split.
- c: The delimiter character.

Return Value
The array of new strings resulting from the split.
NULL if any allocation fails.
The returned structure will be released using:
1) free() on each string in the array;
2) free() the array itself.

Description
Allocates memory (using malloc(3)) and returns an array of strings
 obtained by splitting ’s’ using the character ’c’ as a delimiter.
Each string in the returned array is allocated independently.
The array of pointers itself is also allocated dynamically.
The returned array must be NULL terminated.
*/

#include "libft.h"

// helper function to count the number of string to create.
static size_t	ft_split_count(const char *str, const char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (!*str)
			break ;
		while (*str != c && *str)
			str++;
		count++;
	}
	return (count);
}

// helper function to get lenght of splitted string
// count lenght for str to delimiter c or end of string
static size_t	ft_split_len(const char *str, const char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

// helper function to free memory properly in case of error
// free memory and set pointer to NULL
// set pointer to NULL allow to retrieve error in case of trying to
//	read or write data in memory address that have been free earlier.
static void	ft_split_free(char **split)
{
	while (*split)
	{
		free(*split);
		*split++ = NULL;
	}
	free(split);
	split = NULL;
}

// helper function to create substring
// copy src to dest till delimiter or end of string
// NULL terminate in place of delimiter match
// return pointer to last delimiter match
static char	*ft_split_copy(char *dst, const char *src, const char c)
{
	while (*src && *src != c)
		*dst++ = *src++;
	*dst = '\0';
	return ((char *)src);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	*p_str;
	size_t	i;

	p_str = (char *)s;
	i = 0;
	split = ft_calloc(ft_split_count(s, c) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (*p_str)
	{
		while (*p_str == c && *p_str)
			p_str++;
		if (*p_str != c && *p_str)
		{
			split[i] = ft_calloc(ft_split_len(p_str, c) + 1, sizeof(char));
			if (!split[i])
			{
				ft_split_free(split);
				return (NULL);
			}
			p_str = ft_split_copy(split[i], p_str, c);
			i++;
		}
	}
	return (split);
}
