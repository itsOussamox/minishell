/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:36:51 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/03 11:45:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*output;

	if (!s || !f)
		return (0);
	output = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!output)
		return (0);
	i = 0;
	while (s[i])
	{
		output[i] = (*f)(i, s[i]);
		i++;
	}
	output[i] = 0;
	return (output);
}
