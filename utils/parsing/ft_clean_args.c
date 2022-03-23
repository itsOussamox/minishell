/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:00:50 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/14 17:05:25 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**set_man_err_null(t_state *state)
{
	state->man_err = 1;
	return (NULL);
}

static char	**ft_put_syntax_error(t_state *state, int syntax_code)
{
	char	*message;

	if (syntax_code == 1)
		message = ft_strdup("syntax error due to unclosed quotes\n");
	else if (syntax_code == 2)
		message = ft_strdup("syntax error near unexpected token\n");
	else if (syntax_code == 3)
		message = ft_strdup("ambiguous redirect\n");
	else
		message = ft_strdup("VERY unexpected error occurred.\n");
	if (!message)
		ft_free_exit(state, OUT_OF_MEM);
	state->status = 258;
	ft_put_error(NULL, message);
	free(message);
	message = NULL;
	return (set_man_err_null(state));
}

char	*ft_expand_str(t_state *state, char *old_str)
{
	unsigned int	i;
	char			*new_str;

	new_str = NULL;
	i = 0;
	if (ft_strlen(old_str) == 1)
		return (ft_strdup("$"));
	while (old_str[i] && i < ft_strlen(old_str))
	{
		while (old_str[i] && old_str[i] != ENV_SIGN)
			new_str = ft_charjoin(new_str, old_str[i++]);
		if (!ft_check_end(&new_str, old_str, i))
			break ;
		i++;
		if (old_str[i] && ft_isdigit(old_str[i]))
		{
			i++;
			continue ;
		}
		new_str = ft_add_expanded_env(state, new_str, old_str, &i);
	}
	return (new_str);
}

static char	**ft_expand(t_state *state, char **cmd)
{
	unsigned int	i;
	char			**output;
	char			*tmp;

	i = 0;
	output = NULL;
	tmp = NULL;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], ENV_SIGN))
			output = ft_expand_arg(state, output, cmd[i]);
		else if (ft_strchr(cmd[i], EXIT_STATUS))
			output = ft_expand_exit(state, output, cmd[i]);
		else
			output = ft_add_arg(output, cmd[i]);
		i++;
	}
	ft_free_matrix(cmd);
	return (output);
}

char	**ft_clean_args(t_state *state)
{
	char	**cmd;
	int		syntax_code;

	if (ft_empty_line(state->line))
		return (set_man_err_null(state));
	ft_token(state->line);
	cmd = ft_split_args(state->line, DELIMIT);
	cmd = ft_check_tokens(cmd);
	if (!cmd)
		ft_free_exit(state, OUT_OF_MEM);
	syntax_code = ft_check_syntax(state, cmd, state->line);
	if (syntax_code != 0)
	{
		ft_free_matrix(cmd);
		return (ft_put_syntax_error(state, syntax_code));
	}
	cmd = ft_expand(state, cmd);
	cmd = ft_replace_wildcard(state, cmd);
	if (!cmd)
		return (set_man_err_null(state));
	return (cmd);
}
