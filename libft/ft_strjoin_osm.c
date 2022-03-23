/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_osm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:15:14 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 18:16:45 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_osm(char *s1, char *s2)
{
	char	*output;
	size_t	j;
	size_t	i;
	size_t	final_len;

	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		s1 = ft_strdup("");
	final_len = ft_strlen(s1) + ft_strlen(s2);
	output = (char *) malloc((final_len + 1) * sizeof(char));
	if (!output)
		return (0);
	i = 0;
	j = 0;
	while (s1[j])
		output[i++] = s1[j++];
	j = 0;
	while (s2[j])
		output[i++] = s2[j++];
	output[i] = 0;
	free(s1);
	s1 = NULL;
	return (output);
}
