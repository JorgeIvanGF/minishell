/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:29:04 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/15 20:13:40 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cuenta_palabras(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	ft_free_all(char **arr, int i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

static char	**ft_split_words(char **arr, char const *s, char c, int wc)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (i < wc)
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		start = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		arr[i] = ft_substr(s, start, j - start);
		if (!arr[i])
		{
			ft_free_all(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_cuenta_palabras(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (ft_split_words(result, s, c, word_count));
}

// int main(void)
// {
// 	char **result;
// 	int i = 0;

// 	result = ft_split("Hola, mundo, esto es 42", ',');  // Divide por la coma
// 	while (result[i] != NULL)
// 	{
// 		printf("Palabra %d: %s\n", i + 1, result[i]);
// 		free(result[i]);  // Liberar cada subcadena
// 		i++;
// 	}
// 	free(result);  // Liberar el array principal
// 	return (0);
// }