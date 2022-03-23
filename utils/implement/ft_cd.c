/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:24:23 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/15 09:32:23 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(char *pwd)
{
	if (pwd)
	{
		free(pwd);
		pwd = NULL;
	}
	pwd = getcwd(NULL, PATH_MAX);
	return (pwd);
}

void	ft_chdir_home(t_state *state)
{
	char	*tmp;

	if (!state->home || !state->home->value)
	{
		ft_put_error("cd", "HOME not set.\n");
		state->status = 1;
		return ;
	}
	tmp = ft_strdup(state->pwd);
	if (chdir(state->home->value) == -1)
		ft_free_puterror(state, state->home->value, tmp);
	else
		ft_chdir_update(state, tmp);
}

static void	ft_chdir_back(t_state *state)
{
	char	*tmp;

	if (!state->oldpwd)
	{
		ft_put_error("cd", "OLDPWD not set.\n");
		state->status = 1;
		return ;
	}
	tmp = ft_strdup(state->pwd);
	if (!tmp)
		ft_free_exit(state, OUT_OF_MEM);
	if (chdir(state->oldpwd) == -1)
		ft_free_puterror(state, state->oldpwd, tmp);
	else
		ft_chdir_update(state, tmp);
}

static void	ft_chdir(t_state *state, char *dir_name)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_pwd(tmp);
	if ((!ft_strcmp(dir_name, ".") || !ft_strcmp(dir_name, ".."))
		&& errno == ENOENT)
	{
		ft_free_puterror(state, ".", tmp);
		return ;
	}
	else if (errno == ENOENT || !tmp)
		tmp = ft_strdup(state->pwd);
	if (chdir(dir_name) == -1)
		ft_free_puterror(state, dir_name, tmp);
	else
		ft_chdir_update(state, tmp);
}

void	ft_cd(t_state *state, t_cmd *current_cmd)
{
	if (current_cmd->num_of_args == 1)
	{
		ft_chdir_home(state);
		return ;
	}
	if (!ft_strcmp(current_cmd->args[1], "--"))
		ft_chdir_home(state);
	else if (!ft_strcmp(current_cmd->args[1], "-"))
		ft_chdir_back(state);
	else
		ft_chdir(state, current_cmd->args[1]);
}
