/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:29:47 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 14:45:50 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

/* int	main(void)
{
	char	letter;

	letter = 'h';
	printf("Original: %c, Uppercase: %c\n", letter, ft_toupper(letter));

	letter = 'H';
	printf("Original: %c, Uppercase: %c\n", letter, ft_toupper(letter));

	letter = '!';
	printf("Original: %c, Uppercase: %c\n", letter, ft_toupper(letter));

	return (0);
} */