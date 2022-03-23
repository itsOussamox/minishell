/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:41:02 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 15:06:15 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_matrixes(char **m1, char **m2)
{
	ft_free_matrix(m1);
	ft_free_matrix(m2);
}

void	ft_cpy_matrix(char **input, char **output, unsigned int *i)
{
	unsigned int	j;

	j = 0;
	while (input && input[j])
	{
		output[*i] = ft_strdup(input[j]);
		if (!output[*i])
		{
			ft_free_args_len(output, *i);
			return ;
		}
		(*i)++;
		j++;
	}
}
