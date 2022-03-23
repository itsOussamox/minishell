/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:03:07 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/14 16:36:50 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_loop_pipe(t_state *state, t_cmd *current_node)
{
	int	i;

	i = 0;
	while (i < state->pipes + 1 && current_node)
	{
		if (current_node->next == NULL)
			state->sig = 1;
		state->pids[i] = fork();
		if (state->pids[i] == -1)
			ft_free_setup(state, -1);
		if (state->pids[i] == 0)
			ft_pipe_it(state, current_node, i);
		while (current_node && current_node->token != PIPE)
			current_node = current_node->next;
		if (!current_node)
			break ;
		current_node = current_node->next;
		i++;
	}
}

int	ft_get_pipes(t_cmd **cmd_tree)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = *cmd_tree;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	ft_setup_pipe(t_state *state)
{
	int	i;

	i = 0;
	state->fds = malloc((state->pipes) * sizeof(int *));
	if (!state->fds)
		ft_free_exit(state, OUT_OF_MEM);
	while (i < state->pipes)
	{
		state->fds[i] = malloc(2 * sizeof(int));
		if (!state->fds[i])
			ft_free_setup(state, i);
		i++;
	}
	state->pids = malloc((state->pipes + 1) * sizeof(int));
	if (!state->pids)
		ft_free_setup(state, 0);
	i = -1;
	while (++i < state->pipes)
	{
		if (pipe(state->fds[i]) == -1)
		{
			ft_put_error("pipe", "broken pipe error\n");
			ft_free_pipefds(state, i);
		}
	}
}

void	ft_pipe_it(t_state *state, t_cmd *current_cmd, int i)
{
	if (i == 0)
		dup2(state->fds[i][1], 1);
	else if (i == state->pipes)
		dup2(state->fds[i - 1][0], 0);
	else
	{
		dup2(state->fds[i - 1][0], 0);
		dup2(state->fds[i][1], 1);
	}
	ft_close(state);
	ft_exec_cmd(state, current_cmd);
	if (state->sig)
		ft_handle_status(state);
	exit(state->status);
}
