/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:28:34 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/08 15:28:36 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	index;
	size_t	index2;

	index = ft_strlen(s1);
	index2 = 0;
	while (s2[index2] != '\0')
	{
		s1[index] = s2[index2];
		index++;
		index2++;
	}
	s1[index] = '\0';
	return (s1);
}
