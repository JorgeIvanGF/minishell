/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:27:54 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 18:36:32 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (*str == (unsigned char) c)
			return ((void *)str);
		str++;
		i++;
	}
	return (NULL);
}

// int     main(void)
// {
//     const char  str[] = "Hello, world!";
//     char        ch = 'l';
//     char        *result;

//     result = ft_memchr(str, ch, sizeof(str));
//     if (result != NULL)
//         printf("Character '%c' found at position: %ld\n", ch, result - str);
//     else
//         printf("Character '%c' not found.\n", ch);

//     return (0);
// }