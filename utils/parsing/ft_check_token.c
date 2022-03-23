/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:28:20 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 20:30:12 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_istoken(char c)
{
	return (c == PIPE || c == REDIN || c == REDOUT
		|| c == APPEND || c == HEREDOC);
}

/*
	This function checks if there is a token '<', '>', '|'..
	inside of a given string.
*/
int	ft_contains_token(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (ft_istoken(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_str_istoken(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_istoken(str[i]))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (str[i - 1]);
}

char	ft_token_to_char(char token)
{
	if (token == PIPE)
		return ('|');
	if (token == REDIN || token == HEREDOC)
		return ('<');
	if (token == REDOUT || token == APPEND)
		return ('>');
	return (token);
}

char	*ft_token_to_str(char *tokenized_str)
{
	unsigned int	i;
	char			*output;
	unsigned int	size;

	if (!tokenized_str)
		return (NULL);
	i = 0;
	size = ft_strlen(tokenized_str);
	output = (char *) malloc((size + 1) * sizeof(char));
	while (tokenized_str[i])
	{
		output[i] = ft_token_to_char(tokenized_str[i]);
		i++;
	}
	return (output);
}
