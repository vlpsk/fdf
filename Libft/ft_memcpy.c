/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:58:51 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/05 14:59:12 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*buff;
	unsigned char	*bsrc;
	size_t			i;

	i = 0;
	buff = (unsigned char *)dest;
	bsrc = (unsigned char *)src;
	while (i < n)
	{
		buff[i] = bsrc[i];
		i++;
	}
	return (dest);
}
