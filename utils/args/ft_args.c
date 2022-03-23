/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:25:30 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/12 14:40:54 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_args_len(char **args, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		free(args[i]);
		args[i++] = NULL;
	}
	free(args);
	args = NULL;
	return (NULL);
}

unsigned int	ft_args_len(char **args)
{
	unsigned int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**ft_init_args(char *init)
{
	char			**output;
	int				len;

	len = 2 - (init == NULL);
	output = (char **) malloc(len * sizeof(char *));
	if (!output)
		return (NULL);
	if (len == 1)
	{
		output[0] = NULL;
		return (output);
	}
	output[0] = ft_strdup(init);
	if (!output[0])
	{
		free(output);
		return (NULL);
	}
	output[1] = NULL;
	return (output);
}

char	**ft_add_arg(char **args, char *new_arg)
{
	unsigned int	i;
	unsigned int	len;
	char			**new_args;

	i = 0;
	if (!args)
		return (ft_init_args(new_arg));
	len = ft_args_len(args) + 2;
	new_args = (char **) malloc(len * sizeof(char *));
	while (args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
			return (NULL);
		i++;
	}
	new_args[i++] = ft_strdup(new_arg);
	if (!new_args[i - 1])
	{
		ft_free_matrix(new_args);
		return (NULL);
	}
	new_args[i] = NULL;
	ft_free_matrix(args);
	return (new_args);
}

char	**ft_merge_args(char **args1, char **args2)
{
	unsigned int	i;
	unsigned int	len;
	char			**output;

	i = 0;
	len = ft_args_len(args1) + ft_args_len(args2) + 1;
	output = (char **) malloc(len * sizeof(char *));
	if (!output)
		return (NULL);
	ft_cpy_matrix(args1, output, &i);
	ft_cpy_matrix(args2, output, &i);
	output[i] = NULL;
	ft_free_matrixes(args1, args2);
	return (output);
}
