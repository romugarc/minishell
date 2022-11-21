#include "../minishell.h"

int	form_tab(t_commands **com, t_f_str f_str, int np)
{
	t_inc	i;
	int		start;

	i.i = 0;
	i.k = 0;
	while(i.i < np)
	{
		i.n = 0;
		i.l_i = 0;
		i.l_j = 0;
		i.l_e = 0;
		i.j = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0 && i.n < (*com)[i.i].nb_infile)
		{
			while ((f_str.sp_chars[i.k] == '5' \
					|| f_str.sp_chars[i.k] == '9') \
					&& f_str.quotes[i.k] == '0')
				i.k += 1;
			start = find_special_char('7', f_str, &i, (*com)[i.i].sgl_cmd[i.j]);
			if (start > -1)
			{
 //               manage_infile(com, &f_str, &start);
			}
			if (((*com)[i.i].sgl_cmd[i.j] != 0 && (*com)[i.i].sgl_cmd[i.j][i.l_e] == '\0') || start == -1)
				i.j += 1;
		}
		if ((*com)[i.i].nb_infile == 0 && f_str.quotes[i.k] != '\0')
			i.k += ft_strlen((*com)[i.i].sgl_cmd[i.j]);
		else if (f_str.quotes[i.k] != '\0')
			i.k += 1;
		i.i += 1;
	}
	return (0);
}