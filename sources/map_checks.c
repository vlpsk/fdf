/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:53:41 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 15:53:52 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		is_decimal(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_ishex(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')
		|| (c >= 'a' && c <= 'f'))
		return (1);
	else
		return (0);
}

int		is_hexadecimal_color(char *str)
{
	int i;

	i = 0;
	if (str[0] == '0' && str[1] == 'x')
	{
		if (ft_strlen(str) > 8)
			return (0);
		i = 2;
	}
	else
	{
		if (ft_strlen(str) > 6)
			return (0);
	}
	while (str[i] != '\0')
	{
		if (ft_ishex(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		check_number_of_elements(char **parsed, int x)
{
	if (ft_len(parsed) != x)
		return (0);
	else
		return (1);
}
