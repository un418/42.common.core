/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:53:21 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/24 15:05:48 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

// #include <bsd/string.h>


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
	if (0 || test_all)
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

	// ft_tolower()
	if (0 || test_all)
	{
		printf("--- TEST for ft_tolower() ---\n");
		printf("Test1 ---\n");
		char c = 'a';
		printf("before:%c \n", c);
		printf("before:%d \n", c);
		c = ft_tolower(c);
		printf("after:%c \n",c);
		printf("after:%d \n", c);

		{
			printf("Test2 ---\n");
			char c = 'E';
			printf("before:%c \n", c);
			printf("before:%d \n", c);
			c = ft_tolower((int)c);
			printf("after:%c \n",c);
			printf("after:%d \n", c);
		}
		printf("---------\n");
	}
	// ft_strchr()
	if (0 || test_all)
	{
		printf("--- TEST for ft_strchr() ---\n");
		{
			printf("-- Test1 --\n");
			char *str = "123456789";
			char find = '2';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_strchr(str,find);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test2 --\n");
			char *str = "123456789";
			char find = 'a';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_strchr(str,find);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test3 --\n");
			char *str = "";
			char find = 'a';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_strchr(str,find);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test4 --\n");
			char *str = "";
			char find = '\0';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_strchr(str,find);
			printf("&match:%p \n", match);
		}
		printf("---------\n");
	}

	// ft_strrchr()
	if (0 || test_all)
	{
		printf("--- TEST for ft_strrchr() ---\n");
		{
			printf("-- Test1 --\n");
			char *str = "121";
			char find = '1';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_strrchr(str,find);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test2 --\n");
			char *str = "123456789";
			char find = 'a';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_strrchr(str,find);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test3 --\n");
			char *str = "a";
			char find = 'a';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_strrchr(str,find);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test4 --\n");
			char *str = "";
			char find = '\0';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_strrchr(str,find);
			printf("&match:%p \n", match);
		}
		printf("---------\n");
	}

/* 	
	// ft_strncmp()
	if (0 || test_all)
	{
		printf("--- TEST for ft_strncmp() ---\n");
		{
			printf("-- Test1 --\n");
			char *str1 = "111";
			char *str2 = "111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_strncmp:%d\n",ft_strncmp(str1,str2,3));
			printf("strncmp   :%d\n",strncmp(str1,str2,3));
		}
		{
			printf("-- Test2 --\n");
			char *str1 = "111";
			char *str2 = "1111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_strncmp:%d\n",ft_strncmp(str1,str2,3));
			printf("strncmp   :%d\n",strncmp(str1,str2,3));
		}
		{
			printf("-- Test3 --\n");
			char *str1 = "11111";
			char *str2 = "1111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_strncmp:%d\n",ft_strncmp(str1,str2,3));
			printf("strncmp   :%d\n",strncmp(str1,str2,3));
		}
		{
			printf("-- Test4 --\n");
			char *str1 = "11111";
			char *str2 = "1111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_strncmp:%d\n",ft_strncmp(str1,str2,4));
			printf("strncmp   :%d\n",strncmp(str1,str2,4));
		}
		{
			printf("-- Test5 --\n");
			char *str2 = "";
			char *str1 = "1111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_strncmp:%d\n",ft_strncmp(str1,str2,4));
			printf("strncmp   :%d\n",strncmp(str1,str2,4));
		}
		{
			printf("-- Test5 --\n");
			char *str1 = "11";
			char *str2 = "22";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_strncmp:%d\n",ft_strncmp(str1,str2,1));
			printf("strncmp   :%d\n",strncmp(str1,str2,1));
		}
		{
			printf("-- Test5 --\n");
			char *str1 = "";
			char *str2 = "";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_strncmp:%d\n",ft_strncmp(str1,str2,-1));
			printf("strncmp   :%d\n",strncmp(str1,str2,-1));
		}
		{
			printf("-- Test6 --\n");
			printf("ft_strncmp:%d\n",ft_strncmp("test", "testss", 7));
			printf("strncmp   :%d\n",strncmp("test", "testss", 7));
		}
		{
			printf("-- Test7 --\n");
			printf("ft_strncmp:%d\n",ft_strncmp("", "test", 4));
			printf("strncmp   :%d\n",strncmp("", "test", 4));
		}
		printf("---------\n");
	}
*/
	// ft_memchr()
	if (0 || test_all)
	{
		printf("--- TEST for ft_memchr() ---\n");
		{
			printf("-- Test1 --\n");
			char *str = "123456789";
			char find = '2';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_memchr(str,find,5);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test2 --\n");
			char *str = "123456789";
			char find = 'a';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_memchr(str,find,10);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test3 --\n");
			char *str = "";
			char find = 'a';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_memchr(str,find,10);
			printf("&match:%p \n", match);
		}

		{
			printf("-- Test4 --\n");
			char *str = "";
			char find = '\0';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_memchr(str,find,10);
			printf("&match:%p \n", match);
		}
		{
			printf("-- Test5 --\n");
			char *str = "123456";
			char find = '\0';
			printf("str:%s \n", str);
			printf("find:%c \n", find);
			printf("&str  :%p \n", str);
			char *match = ft_memchr(str,find,10);
			printf("&match:%p \n", match);
		}
		printf("---------\n");
	}
	/* 	
	// ft_memcmp()
	if (0 || test_all)
	{
		printf("--- TEST for ft_memcmp() ---\n");
		{
			printf("-- Test1 --\n");
			char *str1 = "111";
			char *str2 = "111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_memcmp:%d\n",ft_memcmp(str1,str2,3));
			printf("memcmp   :%d\n",memcmp(str1,str2,3));
		}
		{
			printf("-- Test2 --\n");
			char *str1 = "111";
			char *str2 = "1111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_memcmp:%d\n",ft_memcmp(str1,str2,3));
			printf("memcmp   :%d\n",memcmp(str1,str2,3));
		}
		{
			printf("-- Test3 --\n");
			char *str1 = "11111";
			char *str2 = "1111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_memcmp:%d\n",ft_memcmp(str1,str2,3));
			printf("memcmp   :%d\n",memcmp(str1,str2,3));
		}
		{
			printf("-- Test4 --\n");
			char *str1 = "11111";
			char *str2 = "1111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_memcmp:%d\n",ft_memcmp(str1,str2,4));
			printf("memcmp   :%d\n",memcmp(str1,str2,4));
		}
		{
			printf("-- Test5 --\n");
			char *str2 = "";
			char *str1 = "1111";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_memcmp:%d\n",ft_memcmp(str1,str2,4));
			printf("memcmp   :%d\n",memcmp(str1,str2,4));
		}
		{
			printf("-- Test5 --\n");
			char *str1 = "11";
			char *str2 = "22";
			printf("str1:%s \n", str1);
			printf("str2:%s \n", str2);
			printf("ft_memcmp:%d\n",ft_memcmp(str1,str2,1));
			printf("memcmp   :%d\n",memcmp(str1,str2,1));
		}
 		

		// {
		// 	printf("-- Test5 --\n");
		// 	char *str1 = "";
		// 	char *str2 = "";
		// 	printf("str1:%s \n", str1);
		// 	printf("str2:%s \n", str2);
		// 	printf("ft_memcmp:%d\n",ft_memcmp(str1,str2,-1));
		// 	printf("memcmp   :%d\n",memcmp(str1,str2,-1));
		// }

		{
			printf("-- Test6 --\n");
			printf("ft_memcmp:%d\n",ft_memcmp("test", "testss", 7));
			printf("memcmp   :%d\n",memcmp("test", "testss", 7));
		}
		{
			printf("-- Test7 --\n");
			printf("ft_memcmp:%d\n",ft_memcmp("", "test", 4));
			printf("memcmp   :%d\n",memcmp("", "test", 4));
		}
		printf("---------\n");
	}
	 */
	/*
	//ft_strnstr
	// to disable because strnstr used for test need bsd compilation all the time.
	#include <bsd/string.h>
	if (0 || test_all)
	{
		{
			printf("-- Test1 --\n");
			const char *largestring = "Foo Bar Baz";
			const char *smallstring = "Bar";
			printf("ft_strnstr:%p\n",ft_strnstr(largestring, smallstring, 4));
			printf("strnstr   :%p\n",strnstr(largestring, smallstring, 4));
		}
		{
			printf("-- Test2 --\n");
			const char *largestring = "Foo Bar Baz";
			const char *smallstring = "Bar";
			printf("ft_strnstr:%p\n",ft_strnstr(largestring, smallstring, 100));
			printf("strnstr   :%p\n",strnstr(largestring, smallstring, 100));
		}
		{
			printf("-- Test3 --\n");
			const char *largestring = "Foo Bar Baz";
			const char *smallstring = "Bar";
			printf("ft_strnstr:%p\n",ft_strnstr(largestring, smallstring, 7));
			printf("strnstr   :%p\n",strnstr(largestring, smallstring, 7));
		}
			{
			printf("-- Test4 --\n");
			const char *largestring = "Foo Bar Baz";
			const char *smallstring = "Barasdasdasdasadadssd";
			printf("ft_strnstr:%p\n",ft_strnstr(largestring, smallstring, 7));
			printf("strnstr   :%p\n",strnstr(largestring, smallstring, 7));
		}
	}
	 */
	//ft_calloc
	if (0 || test_all)
	{
		{
			printf("-- Test1 --\n");
			printf("calloc   :%p\n",calloc(50, sizeof(long)));
			printf("calloc   :%p\n",calloc(50, sizeof(int)));
			printf("ft_calloc:%p\n",ft_calloc(10, sizeof(size_t)));
			printf("ft_calloc:%p\n",ft_calloc(10, sizeof(char)));
			printf("ft_calloc:%p\n",ft_calloc((size_t)-1, sizeof(char)));
		}
	}
	//ft_atoi
	if (0 || test_all)
	{
		if (1 || test_all)
		{
			// Replicate isspace
			printf("-- Test Helper ft_isspace --\n");
			for (unsigned char i = 0; i < 255; i++)
			{
				if (isspace(i))
					printf("ascii #%d isspace\n",i);
			}
			for (unsigned char i = 0; i < 255; i++)
			{
				if (isspace(i))
					printf("ascii #%d ft_isspace\n",i);
			}

		}
		if (1 || test_all)
		{
			printf("-- Test1 --\n");
			printf("ft_atoi(\"   +1234-+\"):%d\n",ft_atoi("   +1234-+"));
			printf("   atoi(\"   +1234-+\"):%d\n",atoi("   +1234-+"));
		}
		{
			printf("-- Test2 --\n");
			printf("ft_atoi(\"\"):%d\n",ft_atoi(""));
			printf("   atoi(\"\"):%d\n",atoi(""));
		}
		{
			printf("-- Test3 --\n");
			printf("ft_atoi(\"   +-1234-+\"):%d\n",ft_atoi("   +-1234-+"));
			printf("   atoi(\"   +-1234-+\"):%d\n",atoi("   +-1234-+"));
		}
		{
			printf("-- Test$ --\n");
			printf("ft_atoi(\" q  +-91234-+\"):%d\n",ft_atoi(" q  +-91234-+"));
			printf("   atoi(\" q  +-91234-+\"):%d\n",atoi(" q  +-91234-+"));
		}
		{
			printf("-- Test3 --\n");

			// printf("INT64_MAX:%lld\n",INT64_MAX);
			// printf("INT64_MIN:%lld\n",INT64_MIN);
			// printf("INT32_MAX:%d\n",INT32_MAX);
			// printf("INT32_MIN:%d\n",INT32_MIN);
			printf("INT_MAX:%d\n",INT_MAX);
			printf("INT_MIN:%d\n",INT_MIN);


			printf("ft_atoi(\"2147483647\"):%d\n",ft_atoi("2147483647"));
			printf("   atoi(\"2147483647\"):%d\n",atoi("2147483647"));

			printf("ft_atoi(\"-2147483648\"):%d\n",ft_atoi("-2147483648"));
			printf("   atoi(\"-2147483648\"):%d\n",atoi("-2147483648"));
		}
	}
	// ft_strlcat()
	if (0 || test_all)
	{
		printf("--- TEST for ft_strlcat() ---\n");
		if (1)
		{
			printf("Test1: ft_strlcat(dst1,src1,20)\n");
			char src1[] = "ABCDE";
			char dst1[20] = "12345";
			printf("before - src:%s \n",src1);
			printf("before - dst:%s \n",dst1);
			size_t ret = ft_strlcat(dst1,src1,20);
			printf("after - src:%s \n",src1);
			printf("after - dst:%s \n",dst1);
			printf("ft strlen(src): %zu \n",ft_strlen(src1));
			printf("ft return value: %zu \n",ret);
		}
		if (1)
		{
			printf("Test2: ft_strlcat(dst2,src2,0)\n");
			char src2[] = "ABCDE";
			char dst2[] = "12345";
			printf("before - src:%s \n",src2);
			printf("before - dst:%s \n",dst2);
			size_t ret = ft_strlcat(dst2,src2,0);
			printf("after - src:%s \n",src2);
			printf("after - dst:%s \n",dst2);
			printf("ft strlen(src): %zu \n",ft_strlen(src2));
			printf("ft return value: %zu \n",ret);
		}

		if (1)
		{
			printf("Test3: ft_strlcat(dst3,src3,8)\n");
			char src3[] = "ABCDE";
			char dst3[] = "12345";
			printf("before - src:%s \n",src3);
			printf("before - dst:%s \n",dst3);
			size_t ret = ft_strlcat(dst3,src3,8);
			printf("after - src:%s \n",src3);
			printf("after - dst:%s \n",dst3);
			printf("ft strlen(src): %zu \n",ft_strlen(src3));
			printf("ft return value: %zu \n",ret);
		}
		printf("---------\n");
	}
	
	// ft_strdup()
	if (0 || test_all)
	{
		char *s_dup;
		printf("--- TEST for ft_stdup() ---\n");
		printf("ft_strdup return value:%s \n", s_dup= ft_strdup("test dup"));
		free (s_dup);
	}

	// ft_putchar_fd()
	if (0 || test_all)
	{
		printf("--- TEST for ft_putchar_fd() ---\n");
		ft_putchar_fd('A', 1);
		printf("\n");
		printf("---------\n");
	}
	// ft_putstr_fd()
	if (0 || test_all)
	{
		printf("--- TEST for ft_putstr_fd() ---\n");
		ft_putstr_fd("ABCDE12345", 1);
		printf("\n");
		printf("---------\n");
	}
	// ft_putstr_fd()
	if (0 || test_all)
	{
		printf("--- TEST for ft_putstr_fd() ---\n");
		ft_putendl_fd("ABCDE", 1);
		printf("\n");
		printf("---------\n");
	}
	// ft_putnbr_fd()
	if (0 || test_all)
	{
		printf("--- TEST for ft_putnbr_fd() ---\n");
		printf("%d\n",INT_MIN);
		ft_putnbr_fd(INT_MIN, 1);
		printf("\n");
		printf("%d\n",INT_MAX);
		ft_putnbr_fd(INT_MAX, 1);
		printf("\n");
		printf("---------\n");
	}

	// ft_substr()
	if (0|| test_all)
	{
		{
			printf("--- TEST1 for ft_substr() ---\n");
			char *sub = ft_substr("123456789", 0, 7);
			printf("sub=%s", sub);
			free(sub);
			printf("\n");
			printf("---------\n");
		}
		{
			printf("--- TEST2 for ft_substr() ---\n");
			char *sub = ft_substr("123456789", 4, 7);
			printf("sub=%s", sub);
			free(sub);
			printf("\n");
			printf("---------\n");
		}
		{
			printf("--- TEST3 for ft_substr() ---\n");
			char *sub = ft_substr("123456789", 9, 10);
			printf("sub=%s", sub);
			free(sub);
			printf("\n");
			printf("---------\n");
		}
		{
			printf("--- TEST4 for ft_substr() ---\n");
			char *sub = ft_substr("123456789", 12, 12);
			printf("sub=%s", sub);
			free(sub);
			printf("\n");
			printf("---------\n");
		}
		{
			printf("--- TEST2 for ft_substr() ---\n");
			char *sub = ft_substr("123456789", 1, 1);
			printf("sub=%s", sub);
			free(sub);
			printf("\n");
			printf("---------\n");
		}
	}

	// ft_strjoin()
	if (0|| test_all)
	{
		printf("--- TEST for ft_strjoin() ---\n");
		char *join;
		join = ft_strjoin("str1", "str2");
		printf("ft_strjoin(\"str1\", \"str2\")=%s", join);
		free(join);
		printf("\n");
		printf("---------\n");
	}
	// ft_strtrim()
	if (0 || test_all)
	{
		{
			printf("--- TEST for ft_strtrim() ---\n");
			char *trim;
			trim = ft_strtrim("-ABCD-", ".-_");
			printf("ft_strtrim(\"-ABCD-\", \".-_\")=%s", trim);
			free(trim);
			printf("\n");
			printf("---------\n");
		}
		{
			printf("--- TEST for ft_strtrim() ---\n");
			char *trim;
			trim = ft_strtrim("A.B_C-D", "");
			printf("ft_strtrim(\"A.B_C-D\", \"\")=%s", trim);
			free(trim);
			printf("\n");
			printf("---------\n");
		}
		{
			printf("--- TEST for ft_strtrim() ---\n");
			char *trim;
			trim = ft_strtrim("", "");
			printf("ft_strtrim(\"\", \"\")=%s", trim);
			free(trim);
			printf("\n");
			printf("---------\n");
		}
		{
			printf("--- TEST for ft_strtrim() ---\n");
			char *trim;
			trim = ft_strtrim("", "AZE");
			printf("ft_strtrim(\"\", \"AZE\")=%s", trim);
			free(trim);
			printf("\n");
			printf("---------\n");
		}
	}

	// ft_strplit()
	if (1 || test_all)
	{
		printf("--- TEST for ft_strsplit() ---\n");
		if (1 || test_all)
		{
			printf("-- Test1--\n");
			char **split;
			char **p;
	
			split = ft_split(" A BB CCC DDDD ", ' ');
			p = split;
			while (*split)
			{
				printf("%s\n", *split);
				free(*split++);
			}
			free(p);
			printf("---------\n");
		}
		if (1 || test_all)
		{
			printf("-- Test2 --\n");
			char **split;
			char **p;
	
			split = ft_split(" A BB CCC DDDD", ' ');
			p = split;
			while (*split)
			{
				printf("%s\n", *split);
				free(*split++);
			}
			free(p);
			printf("---------\n");
		}
		if (1 || test_all)
		{
			printf("-- Test3 --\n");
			char **split;
			char **p;
	
			split = ft_split("A BB CCC DDDD", ' ');
			p = split;
			while (*split)
			{
				printf("%s\n", *split);
				free(*split++);
			}
			free(p);
			printf("---------\n");
		}
		if (1 || test_all)
		{
			printf("-- Test4--\n");
			char **split;
			char **p;
	
			split = ft_split("A", ' ');
			p = split;
			while (*split)
			{
				printf("%s\n", *split);
				free(*split++);
			}
			free(p);
			printf("---------\n");
		}
		if (1 || test_all)
		{
			printf("-- Test5--\n");
			char **split;
			char **p;
	
			split = ft_split("", ' ');
			p = split;
			while (*split)
			{
				printf("%s\n", *split);
				free(*split++);
			}
			free(p);
			printf("---------\n");
		}
		if (1 || test_all)
		{
			printf("-- Test6 --\n");
			char **split;
			char **p;
	
			split = ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse", ' ');
			p = split;
			while (*split)
			{
				printf("%s\n", *split);
				free(*split++);
			}
			free(p);
			printf("---------\n");
		}
		printf("----------------------------\n");
	}
}
