/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:10:46 by obouadel          #+#    #+#             */
/*   Updated: 2022/01/19 15:20:23 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **array, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(array[i++]);
	free(array);
}
