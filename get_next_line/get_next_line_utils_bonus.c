/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:53 by adaferna          #+#    #+#             */
/*   Updated: 2026/06/20 00:15:19 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*buf_to_stash(int fd, char *stash)
{
	char		buf[BUFFER_SIZE + 1];
	ssize_t		n_read;
	char		*newstash;

	while (!ft_strchr(stash, DELIMITER))
	{
		n_read = read(fd, buf, BUFFER_SIZE);
		if (n_read < 0)
			return (free(stash), stash = NULL, NULL);
		buf[n_read] = '\0';
		if (n_read == 0)
			return (stash);
		if (n_read > 0)
		{
			if (!stash)
				stash = ft_strjoin("", "");
			newstash = ft_strjoin(stash, buf);
			free (stash);
			stash = newstash;
		}
	}
	return (stash);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
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
