/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_exitcode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:06:51 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 20:23:28 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_put_exitcode(t_state *state, char *str)
{
	unsigned int	i;
	char			*output;
	char			*tmp;

	output = NULL;
	tmp = ft_itoa(state->status);
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != EXIT_STATUS)
			output = ft_charjoin(output, str[i++]);
		if (!str[i])
			return (output);
		i += 2;
		output = ft_strjoin_osm(output, tmp);
	}
	free(tmp);
	return (output);
}
