/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:41:26 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/03 11:45:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_len(char *str, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (str[i] != QUOTE)
			count++;
		i++;
	}
	return (count);
}

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
	int		j;

	i = 0;
	j = 0;
	output = (char *) malloc((ft_get_len(str, len) + 1) * sizeof(char));
	if (!output)
		return (0);
	while (i < len)
	{
		if (str[i] == QUOTE)
			i++;
		else
			output[j++] = str[i++];
	}
	output[j] = 0;
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

char	**ft_split_args(char *s, char c)
{
	char	**output;
	size_t	word_count;
	size_t	wc;
	size_t	i;

	wc = -1;
	i = 0;
	word_count = ft_word_count(s, c);
	output = (char **) malloc((word_count + 1) * sizeof(char *));
	if (!output)
		return (0);
	while (++wc < word_count)
	{
		output[wc] = ft_get_next_word(s, &i, c);
		if (!output[wc])
		{
			if (wc > 0)
				ft_free_split(output, wc);
			else
				free(output);
			return (0);
		}
	}
	output[word_count] = 0;
	return (output);
}
