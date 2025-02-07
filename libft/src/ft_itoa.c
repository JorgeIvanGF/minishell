/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:27:21 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 17:44:17 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_n(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*ft_fill_str(char *str, int n, int len)
{
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[--len] = '8';
			n = -214748364;
		}
		n = - (n);
	}
	while (n > 0)
	{
		len--;
		str[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ptr;

	len = ft_len_n(n);
	ptr = (char *) malloc(sizeof(char) * ((size_t) len + 1));
	if (ptr == NULL)
		return (NULL);
	ft_fill_str(ptr, n, len);
	return (ptr);
}

// int main(void)
// {
// 	int num = -2147483648;
// 	char *str = ft_itoa(num);
// 	printf("Número como cadena: %s\n", str);
// 	free(str);  // Liberar memoria después de usar el string
// 	return 0;
// }