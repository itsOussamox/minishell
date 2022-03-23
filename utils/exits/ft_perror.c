/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:35:49 by obouadel          #+#    #+#             */
/*   Updated: 2022/02/24 17:16:13 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_error(char *name, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error, 2);
}

void	ft_perror(t_state *state, char *str, int status)
{
	perror(str);
	state->status = status;
}
