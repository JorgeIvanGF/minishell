/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:35:16 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 14:26:35 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	unsigned char	*p;
	size_t			i;

	p = ptr;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char) value;
		i++;
	}
	return (ptr);
}

// int main(void)
// {
// 	char str[30]= "abcd efgh";
// 	ft_memset(str,'K',4);
// 	int j = 0;
// 	while(str[j] != '\0')
// 	{
// 		printf("%c ", str[j]);
// 		j++;
// 	}
// 	printf("%c", '\n');
// }

// int main(void)
// {
//     int arr_ft[10];
//     int arr_std[10];
//     int i;

//     // Initialize arrays with 0
//     for (i = 0; i < 10; i++)
//     {
//         arr_ft[i] = 1;
//         arr_std[i] = 1;
//     }

// 	for (i = 0; i < 10; i++)
//     {
//         printf("arr_ft[%d] = %d\n", i, arr_ft[i]);
// 	}

// 	for (i = 0; i < 10; i++)
//     {
//         printf("arr_std[%d] = %d\n", i, arr_std[i]);
// 	}

//     // Use ft_memset to set all elements to 1
//     ft_memset(arr_ft, 1, sizeof(int) * 5);

//     // Use standard memset to set all elements to 1
//     memset(arr_std, 1, sizeof(int) * 5);

//     // Print the arrays to check if ft_memset worked correctly
//     printf("Testing ft_memset:\n");
//     for (i = 0; i < 10; i++)
//     {
//         printf("arr_ft[%d] = %d\n", i, arr_ft[i]);
//     }

//     printf("\nTesting standard memset:\n");
//     for (i = 0; i < 10; i++)
//     {
//         printf("arr_std[%d] = %d\n", i, arr_std[i]);
//     }

//     // Compare the results
//     for (i = 0; i < 10; i++)
//     {
//         if (arr_ft[i] != arr_std[i])
//         {
//             printf("\nMismatch at index %d: ft_memset = %d,
//             memset = %d\n", i, arr_ft[i], arr_std[i]);
//             return (1);
//         }
//     }
//     printf("\nft_memset works correctly\n");
//     return (0);
// }
