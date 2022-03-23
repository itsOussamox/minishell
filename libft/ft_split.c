/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:41:26 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 22:27:59 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(char *s, char c)
{
	size_t	output;
	size_t	i;
	int		flag;

	output = 0;
	flag = 1;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (flag && s[i] != c)
		{
			output++;
			flag = 0;
		}
		if (!flag && s[i] == c)
			flag = 1;
		i++;
	}
	return (output);
}

static char	*ft_strndup(char *str, size_t len)
{
	size_t	i;
	char	*output;

	i = 0;
	output = (char *) malloc((len + 1) * sizeof(char));
	if (!output)
		return (0);
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = 0;
	return (output);
}

static char	*ft_get_next_word(char *s, size_t *i, char c)
{
	size_t	k;
	char	*word;

	k = 0;
	while (s[(*i)] == c)
		(*i)++;
	while (s[(*i) + k] != c && s[(*i) + k])
		k++;
	word = ft_strndup((char *)(s + (*i)), k);
	if (!word)
		return (0);
	(*i) += k;
	return (word);
}

static void	ft_free_all(char **array, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(array[i++]);
	free(array);
}

char	**ft_split(char *s, char c)
{
	char	**output;
	size_t	word_count;
	size_t	wc;
	size_t	i;

	if (!s)
		return (NULL);
	wc = -1;
	i = 0;
	word_count = ft_word_count(s, c);
	output = (char **) malloc((word_count + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	while (++wc < word_count)
	{
		output[wc] = ft_get_next_word(s, &i, c);
		if (!output[wc])
		{
			if (wc > 0)
				return (ft_free_all(output, wc), NULL);
			return (free(output), NULL);
		}
	}
	output[word_count] = 0;
	return (output);
}
