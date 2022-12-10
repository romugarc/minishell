#include "../minishell.h"

int removing_quotes(char    **str)
{
    int i;
    int j;
    char    *new_str;
    t_f_str f_str;

    quotes_flags(&f_str, *str);
    i = 0;
    j = 0;
    while (*str[i] != '\0')
    {
        if (*str[i] != '"' && *str[i] != 39 && is_in_quotes(f_str, i) == 0)
            j++;
        i++;
    }
    new_str =  malloc(sizeof(char) * j + 1);
    i = 0;
    j = 0;
    if (!new_str)
        return (1);
    while (*str[i] != '\0')
    {
        if (*str[i] != '"' || *str[i] != 39 && is_in_quotes(f_str, i) == 0)
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    *str = new_str;
    return (0);
}

int remove_quotes(t_commands **cmd, int np)
{
    t_inc   i;
    char    *new_str;

    init_inc(&i);
    while (i.i < np)
    {
        i.j = 0;
        while ((*cmd)[i.i].sgl_cmd[i.j] != NULL)
        {
            removing_quotes(&(*cmd)[i.i].sgl_cmd[i.j]);
            i.j++;
        }
        i.i++;
    }
    return (0);
}