/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:25:24 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 22:31:49 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cpy2out(char *output, size_t *i, char *str)
{
	size_t	j;

	j = 0;
	while (str[j])
		output[(*i)++] = str[j++];
	return (output);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*output;
	size_t	i;
	size_t	final_len;
	int		should_free;

	if (!s2)
		return (ft_strdup(s1));
	should_free = !s1;
	if (!s1)
		s1 = ft_strdup("");
	final_len = ft_strlen(s1) + ft_strlen(s2);
	output = (char *) malloc((final_len + 1) * sizeof(char));
	if (!output)
		return (0);
	i = 0;
	ft_cpy2out(output, &i, s1);
	ft_cpy2out(output, &i, s2);
	output[i] = 0;
	if (should_free)
		free(s1);
	return (output);
}
