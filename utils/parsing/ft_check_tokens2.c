/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tokens2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:53:07 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 22:15:34 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_add_tmp(char **output, char **tmp)
{
	output = ft_add_arg(output, *tmp);
	free(*tmp);
	*tmp = NULL;
	return (output);
}

static char	**ft_split_token(char *str)
{
	unsigned int	i;
	char			**output;
	char			*tmp;

	i = 0;
	output = NULL;
	tmp = NULL;
	while (str[i])
	{
		while (str[i] && !ft_istoken(str[i]))
		{
			tmp = ft_charjoin(tmp, str[i++]);
			if (!tmp)
				return (NULL);
		}
		if (tmp)
			output = ft_add_tmp(output, &tmp);
		tmp = ft_get_next_token(str, tmp, &i);
		if (!tmp)
			break ;
		output = ft_add_tmp(output, &tmp);
	}
	return (output);
}

char	*ft_get_next_token(char *str, char *tmp, unsigned int *i)
{
	while (str[(*i)] && ft_istoken(str[(*i)]))
	{
		if (tmp && tmp[0] != APPEND && tmp[0] != HEREDOC)
			return (tmp);
		if (tmp && (tmp[0] == APPEND || tmp[0] == HEREDOC)
			&& ft_strlen(tmp) == 2)
			return (tmp);
		tmp = ft_charjoin(tmp, str[(*i)++]);
	}
	return (tmp);
}

char	**ft_check_for_token(char *arg, char **output)
{
	char	**split_arg;

	split_arg = NULL;
	if (!ft_contains_token(arg))
	{
		output = ft_add_arg(output, arg);
		if (!output)
			return (NULL);
	}
	else
	{
		split_arg = ft_split_token(arg);
		if (!split_arg)
			return (NULL);
		output = ft_merge_args(output, split_arg);
		if (!output)
			return (NULL);
	}
	return (output);
}
