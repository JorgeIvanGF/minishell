/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:40:37 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 14:17:02 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	n;
	int	signo;

	n = 0;
	signo = 1;
	while ((*str == ' ') || (*str == '\t') || (*str == '\n')
		|| (*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-' || (*str == '+'))
	{
		if (*str == '-')
			signo *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		n = (n * 10) + (*str - '0');
		str++;
	}
	return (n * signo);
}

// int	main(void)
// {
// 	char	str1[] = "   -+12345";
// 	char	str2[] = "	987";
// 	char	str3[] = "  +456abc";	
// 	printf("String: '%s' -> Integer: %d\n Real Function: %d\n", str1,
// 		ft_atoi(str1), atoi(str1)); // Should print: -12345
// 	printf("String: '%s' -> Integer: %d\n Real Function: %d\n", str2,
//  		ft_atoi(str2), atoi(str2)); // Should print: 987
// 	printf("String: '%s' -> Integer: %d\n Real Function: %d\n", str3,
//  		ft_atoi(str3), atoi(str3)); // Should print: 456
// 	return (0);
// }