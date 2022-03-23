/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:36:19 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 17:05:04 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_heredoc(char *line, int *i)
{
	if (line[(*i) + 1] == '<')
	{
		line[*i] = HEREDOC;
		line[(*i) + 1] = HEREDOC;
		(*i)++;
	}
	else
		line[*i] = REDIN;
}

void	ft_replace_append(char *line, int *i)
{
	if (line[(*i) + 1] == '>')
	{
		line[*i] = APPEND;
		line[(*i) + 1] = APPEND;
		(*i)++;
	}
	else
		line[*i] = REDOUT;
}

char	**ft_expand_arg(t_state *state, char **output, char *arg)
{
	char	*tmp;

	tmp = ft_expand_str(state, arg);
	if (!tmp[0])
	{
		free(tmp);
		return (output);
	}
	if (ft_strchr(tmp, EXIT_STATUS))
		output = ft_expand_exit(state, output, tmp);
	else
		output = ft_add_splitted(output, tmp);
	free(tmp);
	return (output);
}

char	**ft_expand_exit(t_state *state, char **output, char *arg)
{
	char	*tmp;

	tmp = ft_put_exitcode(state, arg);
	output = ft_add_arg(output, tmp);
	free(tmp);
	return (output);
}

char	*ft_add_expanded_env(t_state *state, char *new_str,
char *old_str, unsigned int *i)
{
	t_env_var		*env;
	char			*env_name;

	env_name = NULL;
	while (old_str[*i] && (ft_isalnum(old_str[*i]) || old_str[*i] == '_'))
			env_name = ft_charjoin(env_name, old_str[(*i)++]);
	if (!env_name && old_str[*i])
		new_str = ft_charjoin(new_str, '$');
	else
	{
		env = ft_get_env(&state->env, env_name);
		free(env_name);
		if (!env)
			new_str = ft_strjoin_osm(new_str, "");
		else if (ft_is_literal_wildcard(env->value) && !new_str)
			new_str = ft_charjoin(new_str, WILDCARD);
		else
			new_str = ft_strjoin_osm(new_str, env->value);
	}
	return (new_str);
}
