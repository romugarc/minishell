/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:06:54 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/11 17:01:27 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_lstlen(t_envlist *lst)
{
	int			i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	print_export(t_envlist *envc, int oldp_stat, int out)
{
	int			nbr;
	t_envlist	*ref;
	t_envlist	*new;
	t_envlist	*limit;
	t_envlist	*max_limit;

	nbr = 0;
	new = envc;
	ref = envc;
	while (new)
	{
		if (ft_strcmp(ref->var, new->var) > 0)
			ref = new;
		new = new->next;
	}
	new = envc;
	max_limit = envc;
	while (new)
	{
		if (ft_strcmp(max_limit->var, new->var) < 0)
			max_limit = new;
		new = new->next;
	}
	limit = ref;
	while (nbr < ft_lstlen(envc))
	{
		nbr = nbr + 1;
		new = envc;
		while (new)
		{
			if (ft_strcmp(limit->var, new->var) < 0 && ft_strcmp(ref->var, new->var) > 0)
				ref = new;
			new = new->next;
		}
		limit = ref;
		if (envc->env_ == 0 || strcmp_tof(ref->var, "_") == 0)
		{
			if (!(strcmp_tof(ref->var, "PWD") == 1 && oldp_stat == -1))
			{
				ft_putstr_fd("declare -x ", out);
				ft_putstr_fd(ref->var, out);
				if (ref->equal == 0)
					ft_putchar_fd('\n', out);
				else if (ref->equal == 1 && !ref->val)
					ft_putstr_fd("=\"\"\n", out);
				else
				{
					ft_putstr_fd("=\"", out);
					ft_putstr_fd(ref->val, out);
					ft_putstr_fd("\"\n", out);
				}
			}
		}
		ref = max_limit;
	}
}

int	strlen_until_c(char *new_var, char c)
{
	int	i;

	i = 0;
	while (new_var[i] && new_var[i] != c)
		i++;
	return (i);
}

char	*export_varstr(char *new_var, char c)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * strlen_until_c(new_var, c) + 1);
	if (!var)
		return (NULL);
	i = 0;
	while (new_var[i] && new_var[i] != c)
	{
		var[i] = new_var[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

int	is_equal(char *new_var)
{
	int			i;

	i = 0;
	while (new_var[i] && new_var[i] != '=')
		i++;
	if (new_var[i] == '=')
		return (1);
	return (0);
}

int	strlen_after_c(char *new_var, char c)
{
	int	i;
	int	size;

	i = 0;
	while (new_var[i] && new_var[i] != c)
		i++;
	i++;
	size = 0;
	while (new_var[i++])
		size++;
	return (0);
}

char	*export_valstr(char *new_var)
{
	int		i_str;
	int		i_nv;
	char	*str;

	i_str = 0;
	i_nv = 0;
	str = malloc(sizeof(char) * strlen_after_c(new_var, '=') + 1);
	if (!str)
		return (NULL);
	while (new_var[i_nv] && new_var[i_nv] != '=')
		i_nv++;
	i_nv++;
	while (new_var[i_nv])
		str[i_str++] = new_var[i_nv++];
	str[i_str] = '\0';
	return (str);
}

int	ft_lstnew_export(t_envlist **new_lst, char *new_var, char c)
{
	t_envlist	*cpy;

	cpy = malloc(sizeof(t_envlist));
	if (!cpy)
		return (-1);
	cpy->var = export_varstr(new_var, c);
	cpy->equal = is_equal(new_var);
	cpy->val = export_valstr(new_var);
	cpy->next = NULL;
	(*new_lst) = cpy;
	return (0);
}


int	valid_id_exp(char *var, char *cmd, int *oldp_stat)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
	{
		if (ft_isenvarc(var[0], 1) == 0 || ft_isenvarc(var[i], 0) == 0)
		{
			printf("minishell: %s: `%s': not a valid identifier\n", cmd, var);
			return (0);
		}
		i++;
	}
	if (var[i] == '+')
	{
		if (var[i + 1] == '=')
		{
			if (strcmp_tof(var, "PWD") == 1)
				(*oldp_stat) = 0;
			return (2);
		}
		else
		{
			printf("minishell: %s: `%s': not a valid identifier\n", cmd, var);
			return (0);
		}
	}
	if (strcmp_tof(var, "PWD") == 1)
		(*oldp_stat) = 0;
	return (1);
}

int	ft_strndup_addr(char *new_var, char **var_only, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	while (new_var[i] && new_var[i] != c)
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	if (!tmp)
		return (-1);
	i = 0;
	while (new_var[i] && new_var[i] != c)
	{
		tmp[i] = new_var[i];
		i++;
	}
	tmp[i] = '\0';
	(*var_only) = tmp;
	return (0);
}

int	strlen_from_c(char *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!str)
		return (0);
	while (str && str[i] != c)
		i++;
	if (str[i])
		i++;
	while (str[i++])
		size++;
	return (size);
}

int	get_new_val(t_envlist **envc, char *new_val, char c)
{
	int			i;
	int			envi;
	t_envlist	*cpy;

	if (is_equal(new_val) == 0)
		return (0);
	cpy = (*envc);
	cpy->equal = 1;
	i = 0;
	cpy = (*envc);
	if (cpy->val)
		free(cpy->val);
	cpy->val = malloc(sizeof(char) * strlen_from_c(new_val, c) + 1);
	if (!cpy->val)
		return (-1);
	while (new_val[i] && new_val[i] != c)
		i++;
	if (c == '+')
		i++;
	i++;
	envi = 0;
	while (new_val[i])
	{
		cpy->val[envi] = new_val[i];
		envi++;
		i++;
	}
	cpy->val[envi] = '\0';
	(*envc) = cpy;
	return (0);
}

int	get_next_val(t_envlist **envc, char *new_var, char c)
{
	int			i;
	int			j;
	char		*tmp;
	char		*tmp2;
	t_envlist	*cpy;

	i = 0;
	j = 0;
	cpy = (*envc);
	tmp = malloc(sizeof(char) * strlen_from_c(new_var, '=') + 1);
	if (!tmp)
		return (-1);
	while (new_var[i] && new_var[i - 1] != '=')
		i++;
	if (new_var[i - 1] == '=')
		cpy->equal = 1;
	if (new_var[i - 1] == '=' && c == '=')
		free(cpy->val);
	while (new_var[i])
		tmp[j++] = new_var[i++];
	tmp[j] = '\0';
	if (is_equal(new_var) == 1 && c == '=')
	{
		cpy->val = tmp;
		return (0);
	}
	tmp2 = cpy->val;
	cpy->val = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	if (!cpy->val)
		return (-1);
	return (0);
}

int	add_export(t_envlist **envc, char *new_var, char c)
{
	t_envlist	*cpy;
	t_envlist	*new_lst;
	char		*var_only;

	cpy = (*envc);
	if (ft_strndup_addr(new_var, &var_only, c) == -1)
		return (-1);
	while (cpy)
	{
		if (strcmp_tof(cpy->var, var_only) == 1)
			break;
		cpy = cpy->next;
	}
	free(var_only);
	if (!cpy)
	{
		if (ft_lstnew_export(&new_lst, new_var, c) == -1)
			return (-1);
		ft_lstadd_back_env(envc, new_lst);
	}
	else
	{
		if (!cpy->val)
		{
			if (get_new_val(&cpy, new_var, c) == -1)
				return (-1);
		}
		else
			if (get_next_val(&cpy, new_var, c) == -1)
				return (-1);
	}
	return (0);
}

int	ft_export(t_commands cmd, t_exec exec, t_envlist **envc, int *oldp_stat)
{
	int		i;
	int		ret;
	int		out;

	i = 1;
	g_errno = 0;
	if (exec.nb_comm == 1)
		out = cmd.fdout;
	else
		out = 1;
	if (!cmd.sgl_cmd)
		return (-1);
	if (!cmd.sgl_cmd[1])
		print_export((*envc), (*oldp_stat), out);
	else
	{
		while (cmd.sgl_cmd[i])
		{
			ret = valid_id_exp(cmd.sgl_cmd[i], "export", oldp_stat);
			if (ret == 0)
				g_errno = 1;
			if (ret == 1)
				add_export(envc, cmd.sgl_cmd[i], '=');
			else if (ret == 2)
				add_export(envc, cmd.sgl_cmd[i], '+');
			i++;
		}
	}
	if (exec.nb_comm > 1)
		exit(EXIT_SUCCESS);
	return (0);
}