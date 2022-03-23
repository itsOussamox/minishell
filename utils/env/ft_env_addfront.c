/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_addfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:53:35 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 22:24:56 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This function is executed when the export command is run with a +=
	option where it adds to the existing value of the env variable.
*/
void	ft_env_addfront(t_env_var **head, char **new)
{
	t_env_var	*var;
	char		*name;
	char		*temp_value;

	name = new[0];
	name[ft_strlen(name) - 1] = '\0';
	var = ft_get_env(head, name);
	if (!var)
		return ;
	temp_value = ft_strdup(new[1]);
	free(new[1]);
	new[1] = ft_strjoin(var->value, temp_value);
	free(temp_value);
	free(var->value);
	free(var->name);
	free(var->both);
	var->name = name;
	var->value = new[1];
	var->both = new;
}
