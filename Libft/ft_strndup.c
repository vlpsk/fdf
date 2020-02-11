/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:18:20 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/16 20:18:24 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*newstr;
	size_t	i;

	newstr = (char *)malloc(sizeof(char) * (n + 1));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < n && s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
