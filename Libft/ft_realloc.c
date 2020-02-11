/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:33:24 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/16 15:33:27 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*newptr;
	size_t	newsize;

	if (size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (size >= sizeof(ptr))
		newsize = size;
	else
		newsize = sizeof(ptr);
	if (ptr == NULL)
		return ((void *)malloc(sizeof(void) * newsize));
	if (!(newptr = (void *)malloc(sizeof(void) * newsize)))
		return (NULL);
	ft_memcpy(newptr, ptr, newsize);
	free(ptr);
	return (newptr);
}
