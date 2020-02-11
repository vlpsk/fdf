/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:59:01 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/08 15:59:05 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dstlen;
	long long	buff;
	size_t		n;

	dstlen = ft_strlen(dst);
	n = 0;
	buff = size - dstlen - 1;
	if (buff < 0)
		return (ft_strlen(src) + size);
	while (src[n] != '\0' && n < (size_t)buff)
	{
		dst[dstlen + n] = src[n];
		n++;
	}
	dst[dstlen + n] = '\0';
	return (dstlen + ft_strlen(src));
}
