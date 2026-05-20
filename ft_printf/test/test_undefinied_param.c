/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_undefinied_param.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:58:06 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/20 16:09:17 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Test the behavior of printf with undefinied parameter */

#include <stdio.h>

int main(void)
{
	int ret = printf("test %z");
	printf("ret = %d", ret);
}

/* 
RESULT

If we use an undefinied paramater:
	1 - There is warning at compilation time
	2 - Printf write nothing and returns -1
*/