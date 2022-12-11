#include "../minishell.h"

static void	form_new_str(char **new_str, char *str, t_f_str f_str)
{
	int	i;
	int	nb_nq;

	i = 0;
	nb_nq = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != '"' && str[i] != 39 && is_in_quotes(f_str, i) == 0) \
			|| is_in_quotes(f_str, i) != 0)
		{
			(*new_str)[nb_nq] = str[i];
			nb_nq++;
		}
		i++;
	}
	(*new_str)[nb_nq] = '\0';
}

static int	count_not_quotes(char *str, t_f_str f_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != '"' && str[i] != 39 && is_in_quotes(f_str, i) == 0) \
			|| is_in_quotes(f_str, i) != 0)
			j++;
		i++;
	}
	return (j);
}

static int	removing_quotes(char **str)
{
	int		nb_nq;
	char	*tmp_str;
	char	*new_str;
	t_f_str f_str;

	quotes_flags(&f_str, *str);
	nb_nq = count_not_quotes(*str, f_str);
	new_str = malloc(sizeof(char) * nb_nq + 1);
	if (!new_str)
		return (1);
	form_new_str(&new_str, *str, f_str);
	tmp_str = *str;
	*str = new_str;
	free(tmp_str);
	free(f_str.quotes);
	return (0);
}

static int	remove_quotes_intab(t_commands **cmd, int i)
{
	int		j;

	if ((*cmd)[i].nb_infile > 0)
	{
		j = 0;
		while ((*cmd)[i].tab_infile[j] != NULL)
		{
			if (removing_quotes(&(*cmd)[i].tab_infile[j]) == 1)
				return (1);
			j++;
		}
	}
	if ((*cmd)[i].nb_outfile > 0)
	{
		j = 0;
		while ((*cmd)[i].tab_outfile[j] != NULL)
		{
			if (removing_quotes(&(*cmd)[i].tab_outfile[j]) == 1)
				return (1);
			j++;
		}
	}
	return (0);
}

int remove_quotes(t_commands **cmd, int np)
{
	t_inc	i;

	init_inc(&i);
	while (i.i < np)
	{
		i.j = 0;
		while ((*cmd)[i.i].sgl_cmd[i.j] != NULL)
		{
			if (removing_quotes(&(*cmd)[i.i].sgl_cmd[i.j]) == 1)
				return (1);
			i.j++;
		}
		if (remove_quotes_intab(cmd, i.i) == 1)
			return (1);
		i.i++;
	}
	return (0);
}
