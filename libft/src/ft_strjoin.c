/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:15:35 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 19:09:50 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	tot_len;
	char	*ptr;

	tot_len = (size_t)ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(tot_len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy((char *restrict) ptr, (const char *restrict) s1,
		(size_t)ft_strlen(s1) + 1);
	ft_strlcat((char *restrict) ptr, (const char *restrict) s2, tot_len + 1);
	return (ptr);
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