/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowerstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:53:00 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/01 10:26:53 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lowerstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str && str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}
