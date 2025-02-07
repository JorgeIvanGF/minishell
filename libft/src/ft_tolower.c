/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:50:11 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 14:45:41 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
/* int	main(void)
{
	char	letter;

	letter = 'h';
	printf("Original: %c, Lowercase: %c\n", letter, ft_tolower(letter));

	letter = 'H';
	printf("Original: %c, Lowercase: %c\n", letter, ft_tolower(letter));

	letter = '!';
	printf("Original: %c, Lowercase: %c\n", letter, ft_tolower(letter));

	return (0);
} */