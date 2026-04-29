/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:40:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/29 11:38:45 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
 ft_calloc() - allocate dynamic memory init to zero

DESCRIPTION
 The calloc() function allocates memory for an array of nmemb elements
  of size bytes each and returns a pointer to the allocated memory.
 The  memory is set to zero.

 If nmemb or size is 0, then calloc() returns either NULL,
  or a unique pointer value that can later be successfully passed to free().
 If the multiplication of nmemb and size would result in integer overflow,
  then calloc() returns an  error.

 By contrast, an  integer overflow would not be detected 
  in the following call to malloc(),
  with the result that an incorrectly sized block of memory would be allocated:
  malloc(nmemb * size);

IMPLEMENTATION NOTES
 Overflow check:
  We divide the max value of size_t by the size provide in arg,
  it give the max number of element can have this type without overflow.
  So if nmemb is superior to this value,
  that open the door to a Heap-based Buffer Overflow

RETURN VALUE
 - return a pointer to the allocated memory,
   which is suitably aligned for any built-in type.
 - return NULL on error
 - NULL may also be returned by a successful call to calloc()
   with nmemb or size equal to zero.
 */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size > 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
