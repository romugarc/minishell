#include "../minishell.h"

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

int search_expand(char **line, t_envlist *envc)
{
    t_inc   i;
    t_f_str f_str;
    char    *ex_var;
    char    *bef_ex;
    char    *aft_ex;
    char    *tmp_line;

    init_inc(&i);
    quotes_flags(&f_str, *line);
    special_char_flags(&f_str, *line);
    while (line[i.i] != '\0')
    {
        i.n = is_in_quotes(f_str, i.i);
        if (line[i.i] == '$' && i.n != 1)
        {
            i.start = i.i;
            i.l_e = i.start;
            while (*line[i.l_e] != ' ' && *line[i.l_e] != '$' && is_in_quotes(f_str, i.i) == i.n && ft_is_alpha(*line[i.l_e]) != 0)
                i.l_e++;
            ex_var = ft_strdup_s_to_e(*line, i.start, i.l_e);
            if (ex_var == NULL)
                return (1);
            while (envc->next != NULL && i.l_i == 0)
            {
                if (ft_strrcmp(ex_var, envc->var) == 0)
                    i.l_i = 1;
            }
            if (i.l_i = 1)
            {
                bef_ex = ft_strdup_s_to_e(*line, 0, i.start);
                if (bef_ex == NULL)
                    return (1);
                aft_ex = ft_strdup_s_to_e(*line, i.l_e, ft_strlen(*line));
                if (aft_ex == NULL)
                    return (1); //en cas d'erreur de malloc, penser a free ce qui a été malloc avant dans cette fonction
                tmp_line = *line;
                *line = ft_strjoin(bef_ex, envc->val);
                if (*line == NULL)
                    return (1);
                free(tmp_line);
                tmp_line = *line;
                *line = ft_strjoin(*line, aft_ex);
                if (*line == NULL)
                    return (1);
                free(tmp_line);
            }
        }
        i.i++;
    }
    free(f_str.quotes);
    free(f_str.sp_chars);
    return (0);
}

int expand_variable(t_commands *cmd, int np, t_envcpy envc)
{
    t_inc   i;

    init_inc(&i);
    while (i.i < np)
    {
        i.j = 0;
        while ((*cmd)[i.i].sgl_cmd[i.j] != NULL)
        {
            if (search_expand(&line, envc) == 1)
                return (1);
            i.j++;
        }
        i.i++;
    }
    return (0);
}