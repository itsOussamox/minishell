/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:11:26 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/11 15:38:26 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The functions below are removed because they interfere syntax errors
	with tokenization. Our parsing process will completely tokenize the entire
	line, and then check syntax errors right after that.
	We don't want to do both at the same time.
*/

static void	ft_replace_exit(char *line, int *i)
{
	if (line[*i + 1] == '?')
	{
		line[*i] = EXIT_STATUS;
		line[*i + 1] = EXIT_STATUS;
		(*i)++;
	}
	else
		line[*i] = ENV_SIGN;
}

static void	ft_end_quote(char *line, int *i)
{
	char	quote;
	int		replace_env;

	quote = line[*i];
	replace_env = quote == '"';
	line[*i] = QUOTE;
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '$' && replace_env)
			ft_replace_exit(line, i);
		(*i)++;
	}
	if (!line[*i])
		return ;
	line[*i] = QUOTE;
	(*i)++;
}

static void	ft_valid_wildcard(char *line, int *i)
{
	unsigned int	y;

	y = *i;
	if ((*i) != 0 && line[(*i) - 1] != DELIMIT)
	{
		while (line[*i] && line[*i] == '*')
			(*i)++;
		(*i)--;
		return ;
	}
	while (line[y] && line[y] == '*')
		y++;
	if (!line[y] || line[y] == ' ')
	{
		while (line[*i] && line[*i] == '*')
			line[(*i)++] = WILDCARD;
		(*i)--;
	}
	else
	{
		while (line[*i] && line[*i] == '*')
			(*i)++;
		(*i)--;
	}
}

static void	ft_replace_opp(char *line, int *i)
{
	if (line[*i] == '|')
		line[*i] = PIPE;
	else if (line[*i] == '<')
		ft_replace_heredoc(line, i);
	else if (line[*i] == '>')
		ft_replace_append(line, i);
	else if (line[*i] == '$')
		ft_replace_exit(line, i);
	else if (line[*i] == '*')
		ft_valid_wildcard(line, i);
	(*i)++;
}

int	ft_token(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			ft_end_quote(line, &i);
		else if (ft_strchr("<>|$*", line[i]))
			ft_replace_opp(line, &i);
		else if (line[i] == ' ')
			line[i++] = DELIMIT;
		else
			i++;
	}
	return (1);
}
