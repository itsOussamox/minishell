/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:29:23 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 11:41:59 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_ct_quotes(char *value)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (value[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

char	*ft_add_backslash(char *value)
{
	unsigned int	i;
	unsigned int	j;
	char			*output;
	int				quote_count;

	if (!value || !ft_strlen(value))
		return (NULL);
	quote_count = ft_ct_quotes(value);
	if (!quote_count)
		return (ft_strdup(value));
	output = (char *) malloc((ft_strlen(value) + quote_count) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\"')
			output[j++] = '\\';
		output[j++] = value[i++];
	}
	output[j] = 0;
	return (output);
}
