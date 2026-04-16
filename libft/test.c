/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:53:21 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/16 19:18:11 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
int main(void)
{
	int test_all = 0;

	// ft_isalpha()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isalpha() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isalpha(*str));
			str++;
		}
		printf("---------\n");
	}

	// ft_isdigit()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isdigit() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isdigit(*str));
			str++;
		}
		printf("---------\n");
	}

	// ft_isalnum()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isalnum() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isalnum(*str));
			str++;
		}
		printf("---------\n");
	}

	// ft_isascii()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isascii() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isascii(*str));
			str++;
		}
		printf("%d : %d\n",-8,ft_isascii(-8));
		printf("---------\n");
	}

	// ft_isprint()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isprint() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isprint(*str));
			str++;
		}
		printf("%d : %d\n",-8,ft_isprint(-8));
		printf("TAB : %d\n",ft_isprint('	'));
		printf("NULL : %d\n",ft_isprint(0));
		printf("---------\n");
	}

	// ft_strlen()
	if (0 || test_all)
	{
		printf("--- TEST for ft_strlen() ---\n");
		char *str[] = {"ajQT09 #/=@-\\~", "", "	 ", "test", NULL };
		int i = 0;
		while (str[i])
		{
			printf("%s : len =%zu\n",str[i],ft_strlen(str[i]));
			i++;
		}
		printf("---------\n");
		printf("TEST PRINT TAB via printf: %c ; %d\n",9,'	');
		printf("---------\n");

	}

	// ft_memset()
	if (0 || test_all)
	{
		printf("--- TEST for ft_memset() ---\n");
		char str[] = "coucou";
		printf("before:%s \n",str);
		printf("sizeof str[i]=%zu\n",ft_strlen(str));
		ft_memset(str,45,ft_strlen(str));
		printf("after:%s \n",str);
		printf("sizeof str[i]=%zu\n",ft_strlen(str));
		printf("---------\n");
	}

	// ft_bzero()
	if (0 || test_all)
	{
		printf("--- TEST for ft_bzero() ---\n");
		char str[] = "coucou";
		printf("before:%s \n",str);
		printf("sizeof str[i]=%zu\n",ft_strlen(str));
		ft_bzero(str,ft_strlen(str));
		printf("after:%s \n",str);
		printf("sizeof str[i]=%zu\n",ft_strlen(str));
		printf("---------\n");
	}

	// ft_memcpy()
	if (0 || test_all)
	{
		printf("--- TEST for ft_memcpy() ---\n");
		printf("-Test1: \n");
		char src[] = "coucou";
		char dst[] = "-----------";
		printf("before - src:%s \n",src);
		printf("before - dst:%s \n",dst);
		ft_memcpy(dst,src,ft_strlen(src));
		printf("after - src:%s \n",src);
		printf("after - dst:%s \n",dst);
		
		if (0)
		{
			printf("-Test2: Stack Overflow\n");
			char src2[] = "toutou";
			char dst2[] = "---";
			printf("before - src2:%s \n",src2);
			printf("before - dst2:%s \n",dst2);
			ft_memcpy(dst2,src2,ft_strlen(src2));
			printf("after - src2:%s \n",src2);
			printf("after - dst2:%s \n",dst2);
		}

		if (1)
		{
			printf("-Test5: Memory Overlapping\n");
			char src5[] = "123456789";
			char *dst5 = &src5[1];
			printf("before - src5:%s \n",src5);
			printf("before - dst5:%s \n",dst5);
			ft_memcpy(dst5,src5,3);
			printf("after - src5:%s \n",src5);
			printf("after - dst5:%s \n",dst5);
		}
		printf("---------\n");
	}

	// ft_memmove()
	if (0 || test_all)
	{
		printf("--- TEST for ft_memmove() ---\n");
		printf("-Test1: \n");
		char src[] = "coucou";
		char dst[] = "-----------";
		printf("before - src:%s \n",src);
		printf("before - dst:%s \n",dst);
		ft_memmove(dst,src,ft_strlen(src));
		printf("after - src:%s \n",src);
		printf("after - dst:%s \n",dst);
		
		if (0)
		{
			printf("-Test2: Stack Overflow\n");
			char src2[] = "toutou";
			char dst2[] = "---";
			printf("before - src2:%s \n",src2);
			printf("before - dst2:%s \n",dst2);
			ft_memmove(dst2,src2,ft_strlen(src2));
			printf("after - src2:%s \n",src2);
			printf("after - dst2:%s \n",dst2);
		}

		if (1)
		{
			printf("-Test5: Memory Overlapping\n");
			char src5[] = "123456789";
			char *dst5 = &src5[1];
			printf("before - src5:%s \n",src5);
			printf("before - dst5:%s \n",dst5);
			ft_memmove(dst5,src5,3);
			printf("after - src5:%s \n",src5);
			printf("after - dst5:%s \n",dst5);
		}
		printf("---------\n");
	}

	// ft_strlcpy()
	if (0 || test_all)
	{
		printf("--- TEST for ft_strlcpy() ---\n");
		if (1)
		{
			printf("Test1: ft_strlcpy(dst1,src1,ft_strlen(src1)\n");
			char src1[] = "ABCDE";
			char dst1[] = "12345";
			printf("before - src:%s \n",src1);
			printf("before - dst:%s \n",dst1);
			size_t ret = ft_strlcpy(dst1,src1,ft_strlen(src1 + 1));
			printf("after - src:%s \n",src1);
			printf("after - dst:%s \n",dst1);
			printf("ft strlen(src): %zu \n",ft_strlen(src1));
			printf("ft return value: %zu \n",ret);
		}

		if (1)
		{
			printf("Test2: ft_strlcpy(dst2,src2,0)\n");
			char src2[] = "ABCDE";
			char dst2[] = "12345";
			printf("before - src:%s \n",src2);
			printf("before - dst:%s \n",dst2);
			size_t ret = ft_strlcpy(dst2,src2,0);
			printf("after - src:%s \n",src2);
			printf("after - dst:%s \n",dst2);
			printf("ft strlen(src): %zu \n",ft_strlen(src2));
			printf("ft return value: %zu \n",ret);
		}
		
		if (1)
		{
			printf("Test3: ft_strlcpy(dst3,src3,4)\n");
			char src3[] = "ABCDE";
			char dst3[] = "1234";
			printf("before - src:%s \n",src3);
			printf("before - dst:%s \n",dst3);
			size_t ret = ft_strlcpy(dst3,src3,4);
			printf("after - src:%s \n",src3);
			printf("after - dst:%s \n",dst3);
			printf("ft strlen(src): %zu \n",ft_strlen(src3));
			printf("ft return value: %zu \n",ret);
		}
		printf("---------\n");
	}
	
	// ft_toupper()
	if (1 || test_all)
	{
		printf("--- TEST for ft_toupper() ---\n");
		printf("Test1 ---\n");
		char c = 'a';
		printf("before:%c \n", c);
		printf("before:%d \n", c);
		c = ft_toupper(c);
		printf("after:%c \n",c);
		printf("after:%d \n", c);

		{
			printf("Test2 ---\n");
			char c = 'E';
			printf("before:%c \n", c);
			printf("before:%d \n", c);
			c = ft_toupper((int)c);
			printf("after:%c \n",c);
			printf("after:%d \n", c);
		}
		printf("---------\n");



	}
}
