/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:15:35 by jorgutie          #+#    #+#             */
/*   Updated: 2025/03/19 22:16:26 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *goal, const char *start)
{
	char	*temp;

	temp = goal;
	while (*start != '\0')
		*temp++ = *start++;
	*temp = '\0';
	return (goal);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;
	char	*result;

	s1_len = 0;
	s2_len = 0;
	if (s1 == (NULL) && s2 == (NULL))
		return (NULL);
	if (s1 != (NULL))
		s1_len = ft_strlen(s1);
	if (s2 != (NULL))
		s2_len = ft_strlen(s2);
	total_len = (s1_len + s2_len) + 1;
	result = malloc(total_len * sizeof(char));
	if (result == (NULL))
		return (NULL);
	if (s1 != NULL)
		ft_strcpy(result, s1);
	if (s2 != NULL)
		ft_strcpy(result + s1_len, s2);
	return (result);
}

// int main(void)
// {
//     char str1[] = "Hello,54 ";
//     char str2[] = "42 Network!7887";

//     // Using ft_strjoin (your custom function)
//     char *my_join = ft_strjoin(str1, str2);

//     // Standard way to join strings using malloc
//     char *std_join;
//     size_t len = strlen(str1) + strlen(str2) + 1; // +1 for null terminator
//     std_join = (char *)malloc(len * sizeof(char));
//     if (std_join == NULL)
//     {
//         printf("Memory allocation failed for std_join.\n");
//         return (1);
//     }

//     strcpy(std_join, str1);
//     strcat(std_join, str2);

//     // Output the results
//     if (my_join && std_join)
//     {
//         printf("Original string 1:  %s\n", str1);
//         printf("Original string 2:  %s\n", str2);
//         printf("ft_strjoin result:  %s\n", my_join);
//         printf("Standard join:      %s\n", std_join);

//         if (strcmp(my_join, std_join) == 0)
//             printf("Both joined strings are identical!\n");
//         else
//             printf("Joined strings are different!\n");

//         // Free allocated memory
//         free(my_join);
//         free(std_join);
//     }
//     else
//     {
//         printf("Memory allocation failed.\n");
//     }

//     return 0;
// }