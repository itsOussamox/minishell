/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:21:14 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/01 09:52:54 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*output;
	int		i;

	if (!s)
		return (NULL);
	output = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!output)
		return (0);
	i = -1;
	while (s[++i])
		output[i] = s[i];
	output[i] = '\0';
	return (output);
}
