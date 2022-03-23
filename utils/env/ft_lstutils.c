/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:03:39 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 18:46:53 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*ft_lstnew(char **value)
{
	t_env_var	*new_lst;
	char		*tmp;

	new_lst = (t_env_var *) malloc(1 * sizeof(t_env_var));
	if (!new_lst)
		return (NULL);
	new_lst->name = value[0];
	if (!ft_strcmp(new_lst->name, "SHLVL"))
	{
		tmp = ft_strdup(value[1]);
		free(value[1]);
		value[1] = ft_itoa(ft_atoi(tmp) + 1);
		free(tmp);
	}
	new_lst->value = value[1];
	new_lst->both = value;
	new_lst->next = NULL;
	return (new_lst);
}

t_env_var	*ft_lstlast(t_env_var *head)
{
	t_env_var	*current_node;

	if (!head)
		return (NULL);
	current_node = head;
	while (current_node->next)
		current_node = current_node->next;
	return (current_node);
}

void	ft_lstadd_back(t_env_var **head, t_env_var *new)
{
	t_env_var	*last_node;

	if (!head || !new)
		return ;
	last_node = ft_lstlast(*head);
	if (*head)
	{
		new->index = last_node->index + 1;
		last_node->next = new;
		ft_setup_indexes(*head);
	}
	else
	{
		new->index = 0;
		new->sort_index = 0;
		*head = new;
	}
}

void	ft_lstclear(t_env_var **head)
{
	t_env_var	*current_node;
	t_env_var	*temp;

	if (!head || !(*head))
		return ;
	current_node = *head;
	while (current_node)
	{
		temp = current_node->next;
		ft_freenode(current_node);
		current_node = temp;
	}
}

unsigned int	ft_lstsize(t_env_var *head)
{
	t_env_var		*current_node;
	unsigned int	i;

	if (!head)
		return (0);
	i = 0;
	current_node = head;
	while (current_node->next)
	{
		i++;
		current_node = current_node->next;
	}
	return (i);
}
