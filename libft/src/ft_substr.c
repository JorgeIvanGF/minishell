/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:32:26 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 19:11:42 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			s_len;

	if (!s)
		return (NULL);
	s_len = (size_t)ft_strlen(s);
	if (s_len < start)
		len = 0;
	else if (s_len < start + len)
		len = s_len - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// int main(void)
// {
//     char str[] = "Hello, 42 Network!";
//     unsigned int start = 7;
//     size_t len = 10;

//     // Using ft_substr (your custom function)
//     char *my_substr = ft_substr(str, start, len);

//     // Expected behavior based on the input (no standard C substr function)
//     char *expected_substr = "42 Network";

//     // Output the results
//     if (my_substr)
//     {
//         printf("Original string:      %s\n", str);
//         printf("Expected substring:   %s\n", expected_substr);
//         printf("ft_substr result:     %s\n", my_substr);

//         if (strcmp(my_substr, expected_substr) == 0)
//             printf("Both substrings are identical!\n");
//         else
//             printf("Substrings are different!\n");

//         // Free allocated memory
//         free(my_substr);
//     }
//     else
//     {
//         printf("Memory allocation failed.\n");
//     }

//     return 0;
// }