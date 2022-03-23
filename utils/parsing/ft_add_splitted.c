/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_splitted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:57:33 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 11:00:03 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_splitted(char **output, char *tmp)
{
	char	**splitted;

	splitted = ft_split(tmp, ' ');
	if (!splitted)
		return (NULL);
	output = ft_merge_args(output, splitted);
	return (output);
}
