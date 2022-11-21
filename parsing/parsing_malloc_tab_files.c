#include "../minishell.h"

int	malloc_tab_files(t_commands **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			(*c)[i].tab_infile = malloc(sizeof(char *) * ((*c)[i].nb_infile + 1));
			if (!(*c)[i].tab_infile)
				return (1);
		}
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].tab_outfile = malloc(sizeof(char *) * ((*c)[i].nb_outfile + 1));
			if (!(*c)[i].tab_outfile)
				return (1);
		}
		i++;
	}
	return (0);
}