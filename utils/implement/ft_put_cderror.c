/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_cderror.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:20:35 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 21:02:28 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_cderror(t_state *state, char *dir_name)
{
	if (!dir_name)
		return ;
	state->status = 1;
	if (!ft_strncmp(dir_name, ".", 2))
	{
		ft_put_error("cd", "error retrieving current directory\n");
		ft_put_error("getcwd", "cannot access parent directories\n");
		ft_put_error(dir_name, "No such file or directory\n");
	}
	else if (errno == ENOENT)
		ft_put_error(dir_name, "No such file or directory\n");
	else if (errno == EACCES)
		ft_put_error(dir_name, "Permission denied");
	else if (errno == ENOTDIR)
		ft_put_error(dir_name, "Not a directory");
	else
		ft_put_error(NULL, "Error!");
}

void	ft_chdir_update(t_state *state, char *new)
{
	free(state->oldpwd);
	state->oldpwd = new;
	state->pwd = get_pwd(state->pwd);
	state->status = 0;
	ft_update_env(state);
}

void	ft_free_puterror(t_state *state, char *dir_name,
			char *to_free)
{
	ft_put_cderror(state, dir_name);
	free(to_free);
}
