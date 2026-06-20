/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/06/20 00:04:59 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef DELIMITER
#  define DELIMITER '\n'
# endif

# include <unistd.h>
# include <stdlib.h>

/// @brief Reads the next line from a file descriptor.
/// @param fd The file descriptor to read from.
/// @return The next line including the delimiter, or NULL on EOF or error.
char	*get_next_line(int fd);

/// @brief Locates the first occurrence of character c in string s.
/// @param s The string to search in.
/// @param c The character to search for.
/// @return Pointer to the first occurrence of c in s,
///			NULL if not found or if s is NULL.
char	*ft_strchr(char *s, int c);

/// @brief Concatenates two strings into a new string.
/// @param s1 The first string.
/// @param s2 The second string.
/// @return A new string containing s1 followed by s2,
///			or NULL if allocation fails.
/// @note s1 and s2 must be non-NULL. On allocation failure, s1 is freed.
char	*ft_strjoin(char *s1, char *s2);

/// @brief Clean stash by extracting the remaining part after the delimiter.
/// @param s The stash string.
/// @param delimiter The delimiter character.
/// @return The remaining part of the stash after the delimiter,
///			or NULL if allocation fails.
/// @note The input string s is freed.
char	*ft_clean_stash(char *s, char delimiter);

/// @brief Extracts the line from the stash up to the delimiter.
/// @param s The stash string.
/// @param delimiter The delimiter character.
/// @return The line up to and including the delimiter,
///			or NULL if allocation fails.
char	*ft_line_from_stash(char const *s, char delimiter);

/// @brief Reads from file descriptor into stash until delimiter or EOF.
/// @param fd The file descriptor to read from.
/// @param stash The current stash string.
/// @return The updated stash, or NULL on error.
/// @note On error, stash is freed.
char	*buf_to_stash(int fd, char *stash);

#endif