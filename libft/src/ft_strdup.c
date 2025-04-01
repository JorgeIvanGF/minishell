/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:46:08 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 01:04:08 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len;

	if (!s1)
		return (NULL);
	len = (size_t)(ft_strlen(s1));
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s1, len + 1);
	return (copy);
}

// int	main(void)
// {
// 	char	str[] = "Hello, 42!";
// 	char	*std_dup;
// 	char	*my_dup;

// 	// Using strdup (standard function)
// 	std_dup = strdup(str);
// 	// Using ft_strdup (your function)
// 	my_dup = ft_strdup(str);

// 	// Compare both results
// 	if (std_dup && my_dup)
// 	{
// 		printf("Original string:   %s\n", str);
// 		printf("strdup:            %s\n", std_dup);
// 		printf("ft_strdup:         %s\n", my_dup);
// 		if (strcmp(std_dup, my_dup) == 0)
// 			printf("Both strings are identical!\n");
// 		else
// 			printf("Strings are different!\n");
// 	}
// 	else
// 		printf("Memory allocation failed.\n");

// 	// Free allocated memory
// 	free(std_dup);
// 	free(my_dup);
// 	return (0);
// }