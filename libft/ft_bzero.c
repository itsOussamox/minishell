/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:04:04 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/05 10:59:16 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*casted_s;
	size_t			i;

	casted_s = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		casted_s[i] = 0;
		i++;
	}
}
