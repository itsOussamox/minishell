/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:40:17 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 20:04:39 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list {
	void			*content;
	struct s_list	*next;
}	t_list;

/* PART 1 FUNCS */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memmove(void *dst, void *src, size_t len);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
size_t	ft_strlcat(char *dst, char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	*ft_memchr(void *s, int c, size_t n);
int		ft_memcmp(void *s1, void *s2, size_t n);
char	*ft_strnstr(char *big, char *little, size_t len);
int		ft_atoi(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_osm(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
/* PART 2 FUNCS */
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_charjoin(char *s1, char c);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_lowerstr(char *str);

#endif