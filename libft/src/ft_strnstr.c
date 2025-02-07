/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:35:01 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 19:11:07 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if (needle[0] == '\0')
		return ((char *)haystack);
	needle_len = (size_t)(ft_strlen(needle));
	i = 0;
	while (haystack[i] && needle_len + i <= len)
	{
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	haystack[] = "Hel, world";
// 	char	needle[] = ", wo";
// 	char	*result;	
// 	result = ft_strnstr(haystack, needle, 10);
// 	if (result != NULL)
// 		printf("Substring found: %s\n", result);
// 	else
// 		printf("Substring not found\n");
// 	return (0);
// }