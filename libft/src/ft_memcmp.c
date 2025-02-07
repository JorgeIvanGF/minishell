/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:04:37 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 14:25:24 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*us1 != *us2)
			return ((int)(*us1 - *us2));
		i++;
		us1++;
		us2++;
	}
	return (0);
}

// int main(void)
// {
//     char str1[] = "Hello\0abc";
//     char str2[] = "Hello\0xyz";
//     int result;

//     result = ft_memcmp(str1, str2, 5); // Compare 8 bytes
//     printf("Comparison result: %d\n", result);

//     return (0);
// }