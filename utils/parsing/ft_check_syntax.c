/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:02:09 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 20:13:32 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_correct_quotes(char *line)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == QUOTE)
			count++;
		i++;
	}
	return (count % 2 == 0);
}

int	ft_get_token(char *str)
{
	if (!str)
		return (0);
	if (ft_istoken(str[0]) && (!str[1] || (str[0] == str[1] && !str[2])))
		return (str[0]);
	return (0);
}

static int	ft_empty_env(t_state *state, char *str)
{
	char	*name;
	char	*tmp;

	name = ft_expand_str(state, str);
	if (!name)
		return (1);
	tmp = ft_strdup(name);
	free(name);
	name = ft_strtrim(tmp, " \r\n\v\f\t");
	free(tmp);
	if (!name[0])
	{
		free(name);
		return (1);
	}
	free(name);
	return (0);
}

static int	ft_check_syntax_helper(t_state *state, char **cmd, unsigned int i)
{
	if (ft_contains_token(cmd[i])
		&& ft_get_token(cmd[i]) == ft_get_token(cmd[i + 1]))
		return (1);
	if (ft_get_token(cmd[i]) == HEREDOC
		&& ft_get_token(cmd[i + 1]) == APPEND)
		return (1);
	if (ft_get_token(cmd[i]) == REDIN && ft_get_token(cmd[i]) == REDOUT)
		return (1);
	if (ft_contains_token(cmd[i]) && ft_get_token(cmd[i + 1]) == PIPE)
		return (1);
	if ((ft_get_token(cmd[i]) == REDOUT || ft_get_token(cmd[i]) == REDIN
			|| ft_get_token(cmd[i]) == APPEND)
		&& ft_strchr(cmd[i + 1], ENV_SIGN) && ft_empty_env(state, cmd[i + 1]))
		return (3);
	return (0);
}

/*
	DEV NOTE: meaning of each ft_check_syntax return code
	sorry for the hard code, its syntax checking for fuckssake.

	0: success;
	1: unclosed quotes; (ft_correct_quotes())
	2: syntax error near unexpected token;
	2: ambiguous redirect;
	99: something unexpected;
*/
int	ft_check_syntax(t_state *state, char **cmd, char *line)
{
	unsigned int	i;

	i = 0;
	if (!cmd || !cmd[0])
		return (99);
	if (!ft_correct_quotes(line))
		return (1);
	while (cmd[i])
	{
		if (ft_contains_token(cmd[i]) && !cmd[i + 1])
			return (2);
		if ((ft_get_token(cmd[i]) == REDOUT || ft_get_token(cmd[i]) == REDIN)
			&& ft_contains_token(cmd[i + 1]))
			return (2);
		if (ft_get_token(cmd[i]) == PIPE && ft_contains_token(cmd[i + 1])
			&& ft_get_token(cmd[i + 1]) == REDOUT)
			return (2);
		if (ft_check_syntax_helper(state, cmd, i))
			return (ft_check_syntax_helper(state, cmd, i));
		i++;
	}
	return (0);
}
