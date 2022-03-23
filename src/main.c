/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:05:39 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 17:44:30 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	g_state;

void	ft_next_arg_file(t_ptree_nodes *nodes, t_ptree_iters *iters, char **cmd)
{
	iters->file[0] = iters->inside_cmd;
	iters->file[1] = 0;
	if ((nodes->current_node)->token == HEREDOC)
	{
		(nodes->current_node)->eof = ft_strdup(cmd[iters->i]);
		(nodes->current_node)->fd = ft_heredoc((nodes->current_node)->eof);
		if ((nodes->current_node)->fd == -1)
		{
			g_state.status = 1;
			iters->stop_tree = 1;
			return ;
		}
		return ;
	}
	ft_naf_helper(nodes, iters, cmd);
}

void	ft_handle_sigint_parent(int signal)
{
	(void) signal;
	g_state.status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	ft_init_main(char **env)
{
	g_state.line = NULL;
	g_state.man_err = 0;
	g_state.env = ft_setup_env(env);
	if (g_state.env)
	{
		g_state.home = ft_get_env(&g_state.env, "HOME");
		g_state.path = ft_get_env(&g_state.env, "PATH");
	}
	g_state.envtab = ft_update_envtab(&g_state);
	g_state.pid = -1;
	g_state.status = 0;
	g_state.pwd = getcwd(NULL, PATH_MAX);
	g_state.oldpwd = NULL;
	g_state.sig = 0;
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;
	ft_init_main(env);
	ft_prompt(&g_state);
	ft_free_exit(&g_state, 0);
	return (0);
}
