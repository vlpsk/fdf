/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:41:00 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/10 13:41:02 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*newstr;
	size_t	len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	newstr = (char *)malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		newstr[i] = f(i, *s);
		s++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
