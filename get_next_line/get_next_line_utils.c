/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:53 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/09 01:17:43 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_strnchr(const void *s, int c, size_t n)
{
	const unsigned char	*p_s;

	p_s = s;
	while (n--)
	{
		if ( !*p_s || *p_s == (unsigned char)c)
			return ((void *)p_s);
		p_s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*p_dup;
	size_t	len_s;

	len_s = ft_strlen(s);
	p_dup = malloc((len_s + 1) * sizeof(char));
	if (!p_dup)
		return (NULL);
	ft_strlcpy(p_dup, s, len_s + 1);
	return (p_dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p_join;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p_join = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!p_join)
		return (NULL);
	ft_strlcpy(p_join, s1, len_s1 + 1);
	ft_strlcat(p_join, s2, len_s1 + len_s2 + 1);
	return (p_join);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*p_src;

	p_src = src;
	if (size != 0)
	{
		while (--size && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (ft_strlen(p_src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;

	len_dst = ft_strlen(dst);
	if (len_dst >= size)
		return (size + ft_strlen(src));
	else
	{
		ft_strlcpy(dst + len_dst, src, size - len_dst);
		return (len_dst + ft_strlen(src));
	}
}

//create substring from delimiter to the end of the buffer
char	*ft_gnl_substr(char const *s, char delimiter, size_t buf_size)
{
	char	*p_sub;

	// go to delimiter
	while ( *s && *s != delimiter)
	{
		s++;
		buf_size--;
	}
	// pass the delimiter
	s++;
	buf_size--;
	// alloc substr
	p_sub = malloc(buf_size + 1);
	if (!p_sub)
		return (NULL);
	// copy in new allocated str
	ft_strlcpy(p_sub, s, buf_size + 1);

	return (p_sub);
}

// return size to delimiter or to '\0' if delimiter not found
size_t	ft_dstrlen(const char *s, char delimiter)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != delimiter)
		i++;
	return (i);
}

//create substring from start to delimiter
char	*ft_line_from_stash(char const *s, char delimiter)
{
	char	*p_sub;
	char	*p_start;

	// get size for malloc
	p_start = malloc(ft_dstrlen(s, delimiter) + 2);
	p_sub = p_start;
	if (!p_start)
		return (NULL);
	// Copy untill delimeter
	while (*s && *s != delimiter)
	{
		*p_sub++ = *s++;
	}
	*p_sub++ = *s; //last = delimiter or '\0'
	*p_sub = '\0'; // Hope Double Null will no trigger valgrind ...

	return (p_start);
}
