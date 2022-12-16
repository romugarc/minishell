void	ft_exit(char **cmd, int nb_comm)
{
	int	i;
	int	caractere;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 2)
	{
		caractere = 0;
		while (cmd[1][caractere])
		{
			if (ft_isdigit(cmd[1][caractere]) == 0)
				puterror(cmd[1], NULL, 6, 0);
			caractere++;
		}
		if (i <= 2)
		{
			ft_putstr_fd("exit\n", 2);
			exit(ft_atoi(cmd[1]) % 256);
		}
        else
        {
            puterror(cmd[1], NULL, 6, 0);
            exit(EXIT_FAILURE);
        }
	}
	if (i > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_errno = 1;
		return ;
	}
	if (nb_comm == 1)
		ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

int	ft_echo_next_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!str[0])
		return (0);
	if (str[0] == '-' && str[1] == 'n')
		i = 2;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo_first_n(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0); //return 1? pour gérer le cas où y a pas d'argument et on doit afficher newline
	if (!str[0])
		return (1);
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] == 'n')
			i++;
	}
	if (str[0] != '-' && str[1] != 'n')
		return (1);
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	ft_echo(char **tab, t_exec exec, t_commands cmd)
{
	int	line;
	int	out;

	line = 1;
	if (exec.nb_comm == 1)
		out = cmd.fdout;
	else
		out = 1;
	while (tab[line])
	{
		if (ft_echo_next_n(tab[line]) == 0)
			break ;
		line++;
	}
	while (tab[line])
	{
		ft_putstr_fd(tab[line++], out);
		if (tab[line])
			ft_putchar_fd(' ', out);
	}
	if (ft_echo_first_n(tab[1]) == 1)
		ft_putchar_fd('\n', out);
	if (out > 2)
		close(out);
	if (exec.temp != 1)
		exit(EXIT_SUCCESS);
	return (1);
}