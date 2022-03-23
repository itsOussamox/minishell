/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:40:02 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/03 11:45:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	char	to_find;
	int		i;

	i = 0;
	to_find = (char) c;
	while (s[i])
	{
		if (s[i] == to_find)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
