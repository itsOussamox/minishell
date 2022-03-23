/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:11:20 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 17:38:46 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_temp(char **s1)
{
	int	i;

	i = 0;
	if (!s1)
		return ;
	while (s1[i])
	{
		free(s1[i]);
		s1[i++] = NULL;
	}
	free(s1);
	s1 = NULL;
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i++] = NULL;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_free_exit(t_state *state, int status)
{
	write(1, "exit\n", 5);
	if (state->line)
		free(state->line);
	if (state->pwd)
		free(state->pwd);
	if (state->oldpwd)
		free(state->oldpwd);
	ft_free_tree(&state->cmd_tree);
	ft_free_matrix(state->envtab);
	clear_history();
	ft_lstclear(&state->env);
	exit(status);
}

void	ft_free_childs(t_state *state, int status)
{
	if (state->line)
		free(state->line);
	if (state->pwd)
		free(state->pwd);
	if (state->oldpwd)
		free(state->oldpwd);
	ft_free_pipefds(state, state->pipes);
	ft_free_tree(&state->cmd_tree);
	ft_free_matrix(state->envtab);
	clear_history();
	ft_lstclear(&state->env);
	exit(status);
}

t_cmd	*ft_free_tree(t_cmd **head)
{
	t_cmd	*current_node;
	t_cmd	*tmp;

	if (!head || !(*head))
		return (NULL);
	current_node = *head;
	while (current_node)
	{
		free(current_node->name);
		current_node->name = NULL;
		free(current_node->file);
		current_node->file = NULL;
		free(current_node->eof);
		current_node->eof = NULL;
		if (current_node->fd && current_node->fd > -1)
			close(current_node->fd);
		ft_free_matrix(current_node->args);
		tmp = current_node->next;
		free(current_node);
		current_node = tmp;
	}
	return (NULL);
}
