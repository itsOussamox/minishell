/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 08:38:46 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/03 11:45:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;
	size_t			i;

	if (n == 0)
		return (0);
	casted_s1 = (unsigned char *) s1;
	casted_s2 = (unsigned char *) s2;
	i = 0;
	while (casted_s1[i] == casted_s2[i] && i < n - 1)
		i++;
	return (casted_s1[i] - casted_s2[i]);
}
