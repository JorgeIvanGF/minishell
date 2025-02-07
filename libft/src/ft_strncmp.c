/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:26:23 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 15:04:12 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*s1 && *s2 && i < n)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
		i++;
	}
	if (i < n)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

// int	main(void)
// {
// 	char str1[] = "Hellomundo";
// 	char str2[] = "Helli";
// 	char str3[] = "World";
// 	printf("Comparing '%s' with '%s': %d\n",
// 		str1, str2, ft_strncmp(str1, str2, 6)); // Should return 0
// 	printf("Comparing '%s' with '%s': %d\n",
// 		str1, str3, ft_strncmp(str1, str3, 6)); // Should return negative
// 	printf("Comparing '%s' with '%s': %d\n",
// 		str3, str1, ft_strncmp(str3, str1, 6)); // Should return positive
// 	return 0;
// }