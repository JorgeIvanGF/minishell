/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:13:55 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 22:04:01 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start;
	int		end;
	char	*result;

	if (!(s1) || !(set))
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in(s1[start], set))
		start++;
	end = (ft_strlen(s1)) - 1;
	while (end > start && ft_is_in(s1[end], set))
		end--;
	len = (end - start + 1);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1 + start, len + 1);
	result[len] = '\0';
	return (result);
}

// int main(void)
// {
//     char *result;

//     result = ft_strtrim("lorem ipsum dolor sit amet", "tema si");
//     printf("Trimmed string: '%s'\n", result); // Output: "Hello, World!"

//     free(result);
//     return (0);
// }