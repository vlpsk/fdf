/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:44:54 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/23 12:44:59 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	char	*ft_writeline(char **line, char *rem, char *full, int *flag)
{
	int	i;

	i = 0;
	while (full[i])
	{
		if (full[i] == '\n' || full[i] == EOF)
		{
			*line = ft_strsub(full, 0, i);
			if (*line == NULL)
				return (NULL);
			rem = ft_strsub(full, i + 1, ft_strlen(full) - i - 1);
			free(full);
			*flag = 1;
			return (rem);
		}
		else
			i++;
	}
	rem = ft_strdup(full);
	free(full);
	*flag = 0;
	return (rem);
}

static	char	*ft_full(char *rem, char *buff)
{
	char	*full;

	if (rem)
	{
		full = ft_strjoin(rem, buff);
		free(rem);
	}
	else
		full = ft_strdup(buff);
	return (full);
}

static	char	*read_file(int fd, char *rem, char **line, int *flag)
{
	int		ret;
	char	*buff;

	if (!(buff = (char *)ft_memalloc(BUFF_SIZE + 1)))
		return (NULL);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret < 0)
			return (NULL);
		buff[BUFF_SIZE] = '\0';
		if (!(rem = ft_writeline(line, rem, ft_full(rem, buff), flag)))
			return (NULL);
		if (*flag == 1)
		{
			free(buff);
			return (rem);
		}
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	free(buff);
	return (rem);
}

int				get_next_line(const int fd, char **line)
{
	int			flag;
	static char	*rem[12000];

	flag = 0;
	if (fd < 0 || BUFF_SIZE < 1 || line == NULL || fd >= 12000)
		return (-1);
	if (!(rem[fd] = read_file(fd, rem[fd], line, &flag)))
		return (-1);
	if (flag == 1)
		return (1);
	if (!(rem[fd] = ft_writeline(line, rem[fd], rem[fd], &flag)))
		return (-1);
	if (flag == 1)
		return (1);
	else if (rem[fd][0] == '\0' || rem[fd] == NULL)
		return (0);
	else
	{
		*line = ft_strdup(rem[fd]);
		free(rem[fd]);
		rem[fd] = ft_strdup("");
		return (1);
	}
}
