/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:05:11 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/08 15:05:15 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	index;

	index = 0;
	if (ft_strlen(src) < len)
	{
		while (index < ft_strlen(src))
		{
			dst[index] = src[index];
			index++;
		}
		while (index < len)
		{
			dst[index] = '\0';
			index++;
		}
	}
	else
	{
		while (index < len)
		{
			dst[index] = src[index];
			index++;
		}
	}
	return (dst);
}
