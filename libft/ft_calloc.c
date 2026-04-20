/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:40:40 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/20 19:28:34 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
DESCRIPTION
The calloc() function allocates memory for an array of nmemb elements
of size bytes each and returns a pointer to the allocated memory.
The  memory is set to zero.

If nmemb or size is 0, then calloc() returns either NULL,
or a unique pointer value that can later be successfully passed to free().
If the multiplication of nmemb and size would result in integer overflow,
then calloc() returns an  error.

By  contrast, an  integer overflow would not be detected 
in the following call to malloc(),
with the result that an incorrectly sized block of memory would be allocated:
malloc(nmemb * size);

RETURN VALUE
The malloc() and calloc() functions return a pointer to the allocated memory,
which is suitably aligned for any built-in type.
On  error,  these  functions return NULL.
NULL may also be returned by a successful call to malloc() with a size of zero,
or by a successful call to calloc() with nmemb or size equal to zero.

 */

// Overflow check:
// We divide the max value of size by the size of the type in arg,
// it give the max number of element can have this type without overflow.
// So if nmemb is superior of this value,
// that open the door to a Heap-based Buffer Overflow
// Defensive programming:
// Always check division by 0.

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (size > 0 && nmemb > (size_t)-1 / size)
	{
		return (NULL);
	}
	else
	{
		ptr = malloc(nmemb * size);
		if (ptr)
		{
			ft_bzero(ptr, nmemb * size);
			return (ptr);
		}
		else
			return (NULL);
	}
}
