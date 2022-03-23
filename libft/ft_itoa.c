/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 09:54:03 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/06 10:34:56 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_num_len(int n)
{
	unsigned int	uns_n;
	int				output;

	output = 0;
	uns_n = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		uns_n = n * -1;
		output++;
	}
	while (uns_n)
	{
		output++;
		uns_n /= 10;
	}
	return (output);
}

char	*ft_strrev(char *str, int start_index)
{
	size_t	i;
	size_t	j;
	char	tmp;

	i = start_index;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	uns_n;
	char			*output;
	size_t			i;

	output = (char *) malloc((ft_num_len(n) + 1) * sizeof(char));
	if (!output)
		return (0);
	i = 0;
	uns_n = n;
	if (n == 0)
		output[i++] = '0';
	if (n < 0)
	{
		uns_n = n * -1;
		output[i++] = '-';
	}
	while (uns_n)
	{
		output[i++] = (uns_n % 10) + 48;
		uns_n /= 10;
	}
	output[i] = 0;
	return (ft_strrev(output, n < 0));
}
