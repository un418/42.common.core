/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/12 00:15:16 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef DELIMITER
#  define DELIMITER '\n'
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

// utils
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_clean_stash(char *s, char delimiter);
char	*ft_line_from_stash(char const *s, char delimiter);
char	*buf_to_stash(int fd, char *stash);

#endif