/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:35:59 by pgruz11           #+#    #+#             */
/*   Updated: 2024/02/19 19:43:21 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_flags(t_data *d, int mode)
{
	if (mode == 0)
	{
		d->q = 0;
		d->q_flag = 0;
	}
	else
	{
		ft_free_str(d->var);
		ft_free_str(d->val);
	}
}

int	ft_is_num(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

int	ft_is_dir(t_data *d, char *str)
{
	DIR		*dir;

	dir = opendir(str);
	if (dir == NULL)
	{
		ft_error(d, 1, NULL);
		ft_printf_error("cascaribash: cd: %s: %s\n", str, strerror(errno));
		return (1);
	}
	closedir(dir);
	return (0);
}

void	ft_excve_dircheck(char *str)
{
	DIR		*dir;

	dir = opendir(str);
	if (dir == NULL && access(str, F_OK))
	{
		ft_printf_error("cascaribash: %s: %s\n", str, strerror(errno));
		exit (127);
	}
	if (dir == NULL && access(str, X_OK))
	{
		ft_printf_error("cascaribash: %s: %s\n", str, strerror(errno));
		exit (126);
	}
	if (dir != NULL)
	{
		ft_printf_error("cascaribash: %s: is a directory\n", str);
		closedir(dir);
		exit (126);
	}
}
