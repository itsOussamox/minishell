/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 08:58:38 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/03 11:45:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	unsigned char	*my_big;
	unsigned char	*my_little;
	size_t			i;
	size_t			j;

	if (!little[0])
		return ((char *) big);
	my_big = (unsigned char *) big;
	my_little = (unsigned char *) little;
	i = 0;
	while (i < len && my_big[i])
	{
		j = 0;
		while (my_big[i + j] && i + j < len
			&& my_big[i + j] == my_little[j])
		{
			j++;
			if (!my_little[j])
				return ((char *) &my_big[i]);
		}
		i++;
	}
	return (0);
}
