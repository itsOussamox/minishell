/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:06:00 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/03 11:45:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	output;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	output = src_len + ft_min(dst_len, size);
	if (src_len == 0 || size == 0)
		return (output);
	i = 0;
	while (dst_len + i < size - 1 && src[i])
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (output);
}
