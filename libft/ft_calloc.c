/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:44:45 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/18 18:30:58 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocated_ptr;

	allocated_ptr = malloc(nmemb * size);
	if (!allocated_ptr)
		return (0);
	ft_bzero(allocated_ptr, nmemb * size);
	return (allocated_ptr);
}
