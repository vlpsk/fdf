/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:49:27 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/16 14:49:29 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + n;
	newstr = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < size && s2[j] != '\0')
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}
