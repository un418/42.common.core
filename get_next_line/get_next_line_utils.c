/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:53 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/12 00:54:25 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (1)
	{
		if (!*s || *s == c)
			return (s);
		s++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	char	*ptr;
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	while (s1[i1])
		i1++;
	while (s2[i2])
		i2++;
	join = malloc(i1 + i2 + 1);
	ptr = join;
	if (!join)
		return (free(s1), NULL);
	while (*s1)
		*join++ = *s1++;
	while (*s2)
		*join++ = *s2++;
	*join = '\0';
	return (ptr);
}

// clean stash after line processed
//create substring from delimiter to the end of the string
// eq. remove the begining of the string untill the delimitor
char	*ft_clean_stash(char *s, char delimiter)
{
	char	*substr;
	char	*ps;
	char	*psub;
	size_t	i;

	i = 0;
	ps = s;
	while (*s && *s != delimiter)
		s++;
	if (*s == delimiter)
		s++;
	psub = s;
	while (*psub)
	{
		psub++;
		i++;
	}
	substr = malloc(i + 1);
	if (!substr)
		return (free(s), NULL);
	psub = substr;
	while (*s)
		*substr++ = *s++;
	*substr = '\0';
	return (free(ps), psub);
}

//create substring from start to delimiter
char	*ft_line_from_stash(char const *s, char delimiter)
{
	char	*substr;
	char	*p;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != delimiter)
		i++;
	if (s[i] == delimiter)
		i++;
	substr = malloc(i + 1);
	if (!substr)
		return (NULL);
	p = substr;
	while (*s && *s != delimiter)
		*substr++ = *s++;
	if (*s == delimiter)
		*substr++ = *s;
	*substr = '\0';
	return (p);
}
