/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:54:41 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 20:13:04 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_copy(char *output, char *s1, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (i < end - (start - i) + 1)
		output[i++] = s1[start++];
	output[i] = 0;
	return (output);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*output;

	if (!s1)
		return (0);
	if (!set[0])
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_inset(s1[start], set))
		start++;
	if (start == ft_strlen(s1))
		return (ft_calloc(1, sizeof(char)));
	end = ft_strlen(s1) - 1;
	while (s1[end] && ft_inset(s1[end], set))
		end--;
	output = (char *) malloc((end - start + 2) * sizeof(char));
	if (!output)
		return (0);
	ft_copy(output, s1, start, end);
	return (output);
}
