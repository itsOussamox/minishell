/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:35:29 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/14 16:27:27 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_status(t_state *state)
{
	if (state->status == 3)
	{
		write(2, "Quit: 3\n", 8);
		state->status = 131;
	}
	else if (state->status == 2)
	{
		write(2, "\n", 1);
		state->status = 130;
	}
	else if (state->status == 127 || state->status == 126)
		return ;
	else
		state->status = WEXITSTATUS(state->status);
}

static void	ft_cmd_exec(t_state *state, char **paths, char **cmdarg)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_check_path(state, paths, cmdarg);
	if (!path)
	{
		state->status = 127;
		return (ft_put_error(cmdarg[0], "command not found\n"));
	}
	state->pid = fork();
	if (state->pid == -1)
		ft_free_exit(state, 1);
	if (state->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmdarg, state->envtab);
	}
	waitpid(state->pid, &state->status, 0);
	free(path);
}

static void	ft_exec_path(t_state *state, t_cmd *current_cmd)
{
	int	pid;

	if (!ft_check_relative(state, current_cmd->name))
		return ;
	pid = fork();
	if (pid == -1)
		ft_free_exit(state, errno);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(current_cmd->name, current_cmd->args, state->envtab);
	}
	waitpid(pid, &state->status, 0);
}

static void	ft_execve(t_state *state, t_cmd *current_cmd)
{
	char	**paths;
	char	**cmdarg;
	char	*forfree;
	int		i;

	i = -1;
	if (current_cmd->name[0] == 0)
		return (ft_put_error(current_cmd->name, "command not found\n"));
	if (current_cmd->args[0][0] == '.' ||
		ft_strchr(current_cmd->args[0], '/'))
		return (ft_exec_path(state, current_cmd));
	cmdarg = current_cmd->args;
	state->path = ft_get_env(&state->env, "PATH");
	paths = NULL;
	if (state->path)
		paths = ft_split(state->path->value, ':');
	while (paths && paths[++i])
	{
		forfree = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(forfree);
	}
	ft_cmd_exec(state, paths, cmdarg);
	ft_free_temp(paths);
}

void	ft_execute(t_state *state, t_cmd *current_cmd)
{
	if (!ft_strncmp(current_cmd->name, "echo", 5))
		ft_echo(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "cd", 3))
		ft_cd(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "pwd", 4))
		ft_pwd(state);
	else if (!ft_strncmp(current_cmd->name, "env", 4))
		ft_env(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "unset", 6))
		ft_env_unset(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "export", 7))
		ft_env_export(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "exit", 5))
		ft_exit(state, current_cmd);
	else
		ft_execve(state, current_cmd);
}
