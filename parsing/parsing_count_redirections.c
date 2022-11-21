#include "../minishell.h"

static int	is_redirection(t_commands *c, char *str, t_f_str f_str, int *k)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && f_str.quotes[*k] == '0')
		{
			if (str[i + 1] != '>')
				c->nb_outfile += 1;
		}
		else if (str[i] == '<' && f_str.quotes[*k] == '0')
		{
			if (str[i + 1] != '<')
				c->nb_infile += 1;
		}
		i++;
		*k += 1;;
	}
	return (0);
}

void	count_redirections(t_commands **commands, int np, t_f_str f_str)
{
	int	i;
	int	j;
	int	k;
	int	r;

	i = -1;
	k = 0;
	while (++i < np)
	{
		(*commands)[i].nb_outfile = 0;
		(*commands)[i].nb_infile = 0;
		j = 0;
		while ((*commands)[i].sgl_cmd[j] != 0)
		{
			while ((f_str.sp_chars[k] == '5' || \
					f_str.sp_chars[k] == '9') && f_str.quotes[k] == '0')
				k++;
			if (f_str.quotes[k] != '\0')
				r = is_redirection(&(*commands)[i], (*commands)[i].sgl_cmd[j], f_str, &k);
			j++;
		}
	}
}