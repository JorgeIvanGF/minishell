/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:32:35 by jorgutie          #+#    #+#             */
/*   Updated: 2024/11/29 22:44:05 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_clean_return(char **stash, char *line)
{
	free(*stash);
	*stash = NULL;
	return (line);
}

char	*ft_obtain_line(char **stash)
{
	char	*position;
	char	*line;
	char	*new_stash;

	position = ft_strchr_gnl(*stash, '\n');
	if (!position)
	{
		if (*stash[0] == '\0')
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		line = ft_strdup_gnl(*stash);
		return (ft_clean_return(stash, line));
	}
	line = ft_substr_gnl(*stash, 0, position - *stash + 1);
	if (!line)
		return (ft_clean_return(stash, line));
	new_stash = ft_strdup_gnl(position + 1);
	if (!new_stash)
		return (ft_clean_return(stash, line));
	free(*stash);
	*stash = new_stash;
	return (line);
}

char	*ft_read_to_stash(int fd, char *stash)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	readed_bytes;
	char	*tmp;

	readed_bytes = read(fd, buf, BUFFER_SIZE);
	while (readed_bytes > 0)
	{
		buf[readed_bytes] = '\0';
		tmp = ft_strjoin_gnl(stash, buf);
		free(stash);
		if (!tmp)
			return (NULL);
		stash = tmp;
		if (ft_strchr_gnl(stash, '\n'))
			break ;
		readed_bytes = read(fd, buf, BUFFER_SIZE);
	}
	if (readed_bytes == -1)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_obtain_line(&stash);
	return (line);
}

// int main(void)
// {
// 	char *line;
// 	int fd;

// 	fd = open("examplefile.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Line = %s\n\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
