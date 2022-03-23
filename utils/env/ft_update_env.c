/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:38:10 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 18:31:13 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_pwd(t_state *state)
{
	char	*env_str;
	char	**new_env;
	char	*tmp;

	tmp = ft_strdup("PWD=");
	env_str = ft_strjoin(tmp, state->pwd);
	free(tmp);
	new_env = ft_split_env(env_str, '=');
	free(env_str);
	ft_env_update(&state->env, new_env);
}

static void	ft_update_oldpwd(t_state *state)
{
	char	*env_str;
	char	**new_env;
	char	*tmp;

	tmp = ft_strdup("OLDPWD=");
	env_str = ft_strjoin(tmp, state->oldpwd);
	free(tmp);
	new_env = ft_split_env(env_str, '=');
	free(env_str);
	ft_env_update(&state->env, new_env);
}

char	**ft_update_envtab(t_state *state)
{
	t_env_var	*current_node;
	char		**output;
	char		*tmp;
	char		*tmp2;

	output = NULL;
	tmp = NULL;
	current_node = state->env;
	while (current_node)
	{
		tmp = ft_strjoin(current_node->name, "=");
		if (!tmp)
			ft_free_exit(state, OUT_OF_MEM);
		tmp2 = ft_strjoin(tmp, current_node->value);
		free(tmp);
		if (!tmp2)
			ft_free_exit(state, OUT_OF_MEM);
		output = ft_add_arg(output, tmp2);
		free(tmp2);
		current_node = current_node->next;
	}
	return (output);
}

void	ft_update_env(t_state *state)
{
	ft_update_pwd(state);
	ft_update_oldpwd(state);
	ft_free_matrix(state->envtab);
	state->envtab = ft_update_envtab(state);
}
