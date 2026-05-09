/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/09 01:30:11 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# define BUFFER_SIZE 2
# define DELIMITER '\n'

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

// utils
void	*ft_strnchr(const void *s, int c, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_gnl_substr(char const *s, char delimiter, size_t buf_size);
char	*ft_line_from_stash(char const *s, char delimiter);

#endif