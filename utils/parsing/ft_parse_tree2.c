/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tree2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:18:09 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 18:52:50 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_put_errno(char *filename)
{
	if (errno == EACCES)
		ft_put_error(filename, "Permission denied\n");
	else if (errno == EISDIR)
		ft_put_error(filename, "Is a directory\n");
	else
		ft_put_error(filename, "No such file or directory\n");
}

void	ft_naf_helper(t_ptree_nodes *nodes, t_ptree_iters *iters, char **cmd)
{
	(nodes->current_node)->file = ft_strdup(cmd[iters->i]);
	if ((nodes->current_node)->token == APPEND)
		(nodes->current_node)->fd = open((nodes->current_node)->file,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else if ((nodes->current_node)->token == REDOUT)
		(nodes->current_node)->fd = open((nodes->current_node)->file,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if ((nodes->current_node)->token == REDIN)
		(nodes->current_node)->fd = open((nodes->current_node)->file,
				O_RDONLY);
	if ((nodes->current_node)->fd == -1)
	{
		ft_put_errno(nodes->current_node->file);
		iters->stop_tree = 1;
		return ;
	}
}

void	ft_get_file(t_ptree_nodes *nodes, t_ptree_iters *iters, char **cmd)
{
	iters->file[0] = 0;
	ft_notkn_incmd(nodes, iters, cmd);
	return ;
}
