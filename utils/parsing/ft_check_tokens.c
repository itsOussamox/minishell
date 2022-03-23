/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:28:58 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 16:53:04 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_literal_wildcard(char *str)
{
	unsigned int	i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_wildcard(char *str)
{
	unsigned int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != WILDCARD)
			return (0);
		i++;
	}
	return (1);
}

char	**ft_check_tokens(char **cmd)
{
	unsigned int	i;
	char			**output;

	i = 0;
	output = NULL;
	if (!cmd)
		return (NULL);
	while (cmd[i])
		output = ft_check_for_token(cmd[i++], output);
	ft_free_matrix(cmd);
	return (output);
}
