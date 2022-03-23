/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:48:22 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/14 16:28:57 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_pipes(t_state *state)
{
	int	i;

	i = 0;
	if (state->pipes == 0)
		return ;
	while (i < state->pipes)
	{
		free(state->fds[i]);
		state->fds[i] = NULL;
		i++;
	}
	free(state->fds);
	state->fds = NULL;
	free(state->pids);
	state->pids = NULL;
}

t_cmd	*ft_redirect(t_cmd *cmd)
{
	if (cmd->token == REDOUT || cmd->token == APPEND)
	{
		while (cmd->next && (cmd->next->token == REDOUT || \
		cmd->next->token == APPEND))
			cmd = cmd->next;
		if (cmd)
		{
			dup2(cmd->fd, 1);
			close(cmd->fd);
		}
	}
	else if (cmd->token == REDIN || cmd->token == HEREDOC)
	{
		while (cmd->next && (cmd->next->token == REDIN || \
		cmd->next->token == HEREDOC))
			cmd = cmd->next;
		if (cmd)
		{
			dup2(cmd->fd, 0);
			close(cmd->fd);
		}
	}
	return (cmd);
}

static void	ft_execute_pipeline(t_state *state, t_cmd *cmd, t_cmd *sv)
{
	t_cmd	*save;

	save = sv;
	if (!cmd || cmd->token == PIPE)
	{
		if (!save)
			state->status = 0;
		else
			ft_execute(state, save);
		return ;
	}
	else if (cmd->token == 0)
		save = cmd;
	else if (cmd->token == REDOUT || cmd->token == APPEND)
		cmd = ft_redirect(cmd);
	else if (cmd->token == REDIN || cmd->token == HEREDOC)
		cmd = ft_redirect(cmd);
	if (!cmd)
		return ;
	ft_execute_pipeline(state, cmd->next, save);
}

void	ft_exec_cmd(t_state *state, t_cmd *cmd)
{
	ft_execute_pipeline(state, cmd, NULL);
}

void	ft_execution(t_state *state)
{
	int		i;
	t_cmd	*current_node;
	int		status;

	i = -1;
	current_node = state->cmd_tree;
	state->pipes = ft_get_pipes(&state->cmd_tree);
	if (state->pipes == 0)
		return (ft_exec_cmd(state, current_node), ft_handle_status(state));
	ft_setup_pipe(state);
	ft_loop_pipe(state, current_node);
	ft_close(state);
	while (++i < state->pipes + 1)
	{
		if (waitpid(state->pids[i], &status, 0) == state->pids[state->pipes])
				state->status = status;
	}
	state->status = WEXITSTATUS(state->status);
	ft_free_pipes(state);
}
