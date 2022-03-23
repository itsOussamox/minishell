/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:40:54 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/11 14:24:19 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_io(t_state *state)
{
	dup2(state->io[0], STDIN_FILENO);
	dup2(state->io[1], STDOUT_FILENO);
}

void	ft_save_io(t_state *state)
{
	state->io[0] = dup(STDIN_FILENO);
	state->io[1] = dup(STDOUT_FILENO);
}
