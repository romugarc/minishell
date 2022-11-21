#include "minishell.h"

typedef struct t_red
{
    int type;
    char    *name;
    //faire plutot un char * dans une struct malloc ou un char **flag_redirections pour savoir le type de redirection
}   s_red

static char	*ft_strdup_s_to_e(char const *src, size_t n, size_t index)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * ((index - n) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[n] && n < index)
	{
		dest[i] = src[n];
		n++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void    manage_outfile3(t_commands **com, t_f_str *f_str, int *start)
{
    int end;

    end = *start + 1;
	i->k += 1;
	while ((f_str->sp_chars[i->k] < '5' || ((f_str->sp_chars[i->k] == '9' || f_str->sp_chars[i->k] == '6') \
		&& f_str->quotes[i->k] != '0')) && f_str->sp_chars[i->k] != '\0')
	{
		printf("%d\t%c\t%c\n", end, f_str->sp_chars[i->k], f_str.sp_chars[i.k]);
		end += 1;
		i->k += 1;
	}
	i->l_e = end;
	printf("%d\t%d\n", *start, end);
	if ((*com)[i->i].sgl_cmd[i->j] != 0)
	{
		(*com)[i->i].tab_infile[i->n] = ft_strdup_s_to_e((*com)[i->i].sgl_cmd[i->j], *start + 1, end);
		printf("%s2\n", (*com)[i->i].tab_infile[i->n]);
		i->n += 1;
	}
}

void    manage_outfile2(t_commands **com, t_f_str *f_str, int *start)
{
    int end;

    *start = 0;
	end = 0;
	i->j++;
	while ((f_str->sp_chars[i->k] == '6' || f_str->sp_chars[i->k] == '9') && f_str->sp_chars[i->k] != '\0')
		i->k += 1;
	while ((f_str->sp_chars[i->k] < '5' || ((f_str->sp_chars[i->k] == '9' || f_str->sp_chars[i->k] == '6') \
		&& f_str->quotes[i->k] != '0')) && f_str->sp_chars[i->k] != '\0')
	{
		end += 1;
		i->k += 1;
	}
	i->l_e = end;
	printf("%d\t%d\n", *start, end);
	if ((*com)[i->i].sgl_cmd[i->j] != 0)
	{
		(*com)[i->i].tab_infile[i->n] = ft_strdup_s_to_e((*com)[i->i].sgl_cmd[i->j], *start, end);
		printf("%s1\n", (*com)[i->i].tab_infile[i->n]);
		i->n += 1;
	}
}

void    manage_outfile(t_commands **com, t_f_str *f_str, int *start)
{
    int end;

    if (f_str.sp_chars[i.k + 1] == '6')
	{
		i.k += 1;
		start += 1;
	}
	if (f_str.sp_chars[i.k + 1] == '9' && f_str.sp_chars[i.k + 1] != '\0')
	{
		manage_outfile2(com, f_str, start);
	}
	else if (f_str.sp_chars[i.k + 1] != '\0')
	{
		manage_outfile3(com, f_str, start);
	}
}

int form_tab(t_commands **com, t_f_str f_str, int np)
{
    int start;

    start = find_special_char('7', f_str, &i, (*com)[i.i].sgl_cmd[i.j]);
    if (start == -1)
        start = find_special_char('6', f_str, &i, (*com)[i.i].sgl_cmd[i.j]);
    return (0);
}