/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:10:55 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/09 14:11:41 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t index;

	index = 0;
	while (s1[index] == s2[index])
	{
		if (s1[index] == '\0' && s2[index] == '\0')
			return (0);
		else
			index++;
	}
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
