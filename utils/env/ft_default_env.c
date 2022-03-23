/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:09:23 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 17:15:30 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_var	*ft_add_pwd(unsigned int *i)
{
	char		*tmp;
	char		*env_str;
	char		*pwd;
	t_env_var	*var;
	char		**new_env;

	tmp = ft_strdup("PWD=");
	pwd = getcwd(NULL, PATH_MAX);
	env_str = ft_strjoin(tmp, pwd);
	free(tmp);
	free(pwd);
	new_env = ft_split_env(env_str, '=');
	free(env_str);
	var = ft_lstnew(new_env);
	var->index = (*i)++;
	return (var);
}

static void	ft_add_oldpwd(t_env_var **head, unsigned int *i)
{
	char		*env_str;
	char		**new_env;
	t_env_var	*var;

	env_str = ft_strdup("OLDPWD=");
	new_env = ft_split_env(env_str, '=');
	free(env_str);
	var = ft_lstnew(new_env);
	var->index = (*i)++;
	ft_lstadd_back(head, var);
}

t_env_var	*ft_init_default(void)
{
	unsigned int	i;
	t_env_var		*env_lst;

	i = 0;
	env_lst = ft_add_pwd(&i);
	ft_add_oldpwd(&env_lst, &i);
	ft_add_shlvl(&env_lst, &i);
	ft_setup_indexes(env_lst);
	return (env_lst);
}

t_env_var	*ft_edit_default(t_env_var *old_env)
{
	t_env_var		*tmp;
	unsigned int	i;

	i = ft_lstsize(old_env);
	if (!ft_get_env(&old_env, "PWD"))
	{
		tmp = ft_add_pwd(&i);
		ft_lstadd_back(&old_env, tmp);
	}
	if (!ft_get_env(&old_env, "OLDPWD"))
		ft_add_oldpwd(&old_env, &i);
	if (!ft_get_env(&old_env, "SHLVL"))
		ft_add_shlvl(&old_env, &i);
	return (old_env);
}

t_env_var	*ft_default_env(t_env_var *old_env)
{
	t_env_var		*env_lst;

	env_lst = NULL;
	if (!old_env)
		env_lst = ft_init_default();
	else
		env_lst = ft_edit_default(old_env);
	return (env_lst);
}
