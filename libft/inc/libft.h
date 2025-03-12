/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:43:19 by jorgutie          #+#    #+#             */
/*   Updated: 2025/03/10 20:50:21 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>

// Linked Lists Struct_________________________
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Mandatory part__________________________
int		ft_atoi(const char *str);
long	ft_atoi_long(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_free_2d(char **matrix);
void	ft_free(char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *ptr, int value, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_swap(int *a, int *b);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_uitoa(unsigned int n);

// Printf ___________________________________
int		ft_printf(const char *format, ...);
int		ft_printchar(int c);
int		ft_printstring(char *str);
int		ft_printdigit(long n);
int		ft_printhex(long unsigned n, int c);
int		ft_printpointer(void *ptr);

// Get Next Line_______________________

// Definning the Buffer Size
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*ft_read_to_stash(int fd, char *stash);
char	*ft_obtain_line(char **stash);
char	*ft_clean_return(char **stash, char *line);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strdup_gnl(const char *s);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t n);

// Bonus Part_________________________________
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif