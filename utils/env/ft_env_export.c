/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:26:07 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 16:49:15 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_var	*ft_get_sorted_index(t_env_var *head, unsigned int i)
{
	t_env_var		*current_node;

	current_node = head;
	while (current_node)
	{
		if (current_node->sort_index == i)
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

static void	ft_print_env_export(t_env_var *head)
{
	t_env_var		*current_node;
	unsigned int	i;
	unsigned int	lst_size;
	char			*output;

	i = 0;
	lst_size = ft_lstsize(head);
	while (i <= lst_size)
	{
		current_node = ft_get_sorted_index(head, i);
		if (!current_node)
			return ;
		output = ft_add_backslash(current_node->value);
		if (!output)
			printf("declare -x %s\n", current_node->name);
		else
			printf("declare -x %s=\"%s\"\n", current_node->name, output);
		free(output);
		i++;
	}
}

void	ft_env_add(t_env_var **head, char **new)
{
	t_env_var	*new_env_var;

	if (new[0][ft_strlen(new[0]) - 1] == '+')
		new[0][ft_strlen(new[0]) - 1] = '\0';
	new_env_var = ft_lstnew(new);
	ft_lstadd_back(head, new_env_var);
}

void	ft_env_update(t_env_var **head, char **new)
{
	t_env_var	*var;
	char		*name;
	char		*value;

	name = new[0];
	if (name[ft_strlen(name) - 1] == '+')
	{
		ft_env_addfront(head, new);
		return ;
	}
	value = new[1];
	var = ft_get_env(head, name);
	if (!var)
		return ;
	free(var->value);
	free(var->name);
	free(var->both);
	var->name = name;
	var->value = value;
	var->both = new;
}

void	ft_env_export(t_state *state, t_cmd *current_cmd)
{
	unsigned int	i;
	char			**new_var;

	i = 0;
	if (current_cmd->num_of_args == 1)
		ft_print_env_export(state->env);
	else
	{
		while (current_cmd->args[++i])
		{
			new_var = ft_split_env(current_cmd->args[i], '=');
			if (!new_var)
			{
				ft_put_error(current_cmd->args[i], "not a valid identifier\n");
				state->status = 1;
			}
			else if (ft_get_env(&state->env, new_var[0]))
				ft_env_update(&state->env, new_var);
			else
				ft_env_add(&state->env, new_var);
		}
	}
	state->status = 0;
}
