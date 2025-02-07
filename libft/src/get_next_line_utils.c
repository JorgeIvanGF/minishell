/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:32:12 by jorgutie          #+#    #+#             */
/*   Updated: 2024/11/29 22:53:13 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	joined = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1)
				+ ft_strlen_gnl(s2) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (unsigned char)s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * ft_strlen_gnl(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t n)
{
	size_t	strlen;
	size_t	sublen;
	char	*newstr;
	size_t	i;

	if (!s)
		return (NULL);
	strlen = ft_strlen_gnl(s);
	if (start >= strlen)
		return (ft_strdup_gnl(""));
	sublen = n;
	if (sublen > (strlen - start))
		sublen = strlen - start;
	newstr = (char *)malloc(sublen + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < sublen)
	{
		newstr[i] = s[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

// int main (void)
// {
// 	char s1[] = "Hola amigo";
// 	char *s2= NULL;
// 	char *joined;
// 	char *joined2;

// 	//joined = ft_strdup(s2);
// 	joined2 = strdup(s2);
// 	printf("la union es: %s\n", s2);
// 	printf("la union es: %s\n", joined);
// 	return (0);
// } 
