/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:09:47 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 19:10:28 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	result;
	size_t	dstlen;
	size_t	srclen;

	dstlen = (size_t) ft_strlen((const char *)dst);
	srclen = (size_t) ft_strlen((const char *)src);
	result = srclen + dstlen;
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	i = 0;
	while (src[i] && i < dstsize - dstlen - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (result);
}
/* int	main(void)
{
	char	dest[9] = "Hello";
	char	src[] = " World!";
	size_t	result;

	result = ft_strlcat(dest, src, sizeof(dest));
	printf("Concatenated string: %s\n", dest);
	printf("Length tried to create: %zu\n", result);
	return (0);
} */