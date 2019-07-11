char		*ft_scan(char *buff, char *str, char *tmp)
{
	int		index;

	index = 0;
	while (read(0, buff, 1))
	{
		if (index != 0)
		{
			free(tmp);
			tmp = (char *)malloc(sizeof(char) * index);
			tmp = str;
			free(str);
		}
		str = (char *)malloc(sizeof(char) * (index + 1));
		if (tmp != NULL)
			str = tmp;
		if (buff[0] == '\n' || buff[0] == EOF || buff[0] == '\r')
			break ;
		str[index] = buff[0];
		str[index + 1] = '\0';
		index++;
	}
	if (buff[0] != '\n')
		write(1, "\n", 1);
	return (str);
}

int		main(int argc, char **argv)
{

	/*if (argc != 2)
	{
		ft_putendl("usage: ./fdf source_file");
		return (1);
	}
	else
		read_map(argv[1]);
	return (0);*/

	char scanbuff[1];
	char *str;
	char *tmp;

	if (argc < 2)
	{
		str = NULL;
		tmp = NULL;
		str = ft_scan(scanbuff, str, tmp);
		read_map(str);
	}
	else if (argc == 2)
		read_map(argv[1]);
	else
	{
		ft_putendl("usage: ./fdf source_file");
		return (1);
	}
}