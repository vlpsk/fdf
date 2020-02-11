/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:58:31 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/05 16:58:34 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c,
	size_t n)
{
	unsigned char	ch;
	unsigned char	*cdst;
	unsigned char	*csrc;

	ch = (unsigned char)c;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	while (n--)
	{
		if ((*cdst++ = *csrc++) == ch)
			return (cdst);
	}
	return (NULL);
}
