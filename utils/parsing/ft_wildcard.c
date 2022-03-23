/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:28:11 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/14 17:01:54 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_contains_wildcard(char **cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_is_wildcard(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

static char	**ft_add_wildcard(char **output, char *new_arg)
{
	char			**wildcard;

	wildcard = ft_wildcard();
	if (!wildcard)
		output = ft_add_arg(output, new_arg);
	else
		output = ft_merge_args(output, wildcard);
	return (output);
}

char	**ft_replace_wildcard(t_state *state, char **cmd)
{
	unsigned int	i;
	char			**output;

	(void) state;
	output = NULL;
	if (!cmd)
		return (NULL);
	if (!ft_contains_wildcard(cmd))
		return (cmd);
	i = 0;
	while (cmd[i])
	{
		if (ft_is_wildcard(cmd[i]))
			output = ft_add_wildcard(output, cmd[i]);
		else
			output = ft_add_arg(output, cmd[i]);
		i++;
	}
	ft_free_matrix(cmd);
	return (output);
}

char	**ft_wildcard(void)
{
	struct dirent	*dir;
	char			**wildcard;
	DIR				*directory;

	wildcard = NULL;
	directory = opendir(".");
	if (!directory)
		return (NULL);
	while (69)
	{
		dir = readdir(directory);
		if (!dir)
			break ;
		if (dir->d_name[0] != '.')
			wildcard = ft_add_arg(wildcard, dir->d_name);
	}
	closedir(directory);
	return (wildcard);
}

int	ft_check_end(char **new_str, char *old_str, size_t i)
{
	if (i >= ft_strlen(old_str))
		return (0);
	else if (old_str[i] == ENV_SIGN && i + 1 == ft_strlen(old_str))
	{
		*new_str = ft_charjoin(*new_str, '$');
		return (0);
	}
	return (1);
}
