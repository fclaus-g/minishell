/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:00:53 by pgruz11           #+#    #+#             */
/*   Updated: 2024/02/04 10:48:55 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_delete_var(char **str_tab, int pos)
{
	char	**aux;
	int		i;
	int		j;

	aux = malloc(sizeof(char *) * ft_strdlen(str_tab));
	i = 0;
	j = 0;
	while (str_tab[i] != NULL)
	{
		if (i != pos)
		{
			aux[j] = ft_strdup(str_tab[i]);
			j++;
		}
		i++;
	}
	aux[j] = NULL;
	ft_totalfree(str_tab);
	return (aux);
}

void	ft_unset_env(t_data *d, char *arg)
{
	int	i;

	i = -1;
	while (++i < d->env_size)
	{
		if (!ft_strcmp(d->env_arr[i].title, arg))
		{
			d->env_dup = ft_delete_var(d->env_dup, i);
			return ;
		}
	}
}

void	ft_unset_exp(t_data *d, char *arg)
{
	int		i;
	size_t	len;

	len = ft_strlen(arg);
	i = -1;
	while (d->env_exp[++i] != NULL)
	{
		if ((!ft_strncmp(d->env_exp[i], arg, len))
			&& (d->env_exp[i][len] == '=' || d->env_exp[i][len] == '\0'))
		{
			d->env_exp = ft_delete_var(d->env_exp, i);
			return ;
		}
	}
}

void	bi_unset(t_data *d, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd_tab[++i] != NULL)
	{
		ft_unset_env(d, cmd->cmd_tab[i]);
		ft_unset_exp(d, cmd->cmd_tab[i]);
		ft_get_envarray(d);
	}
	d->exit_code = 0;
}

/**
 * 1) Check cada arg[i] (menos 0) de unset en env_arr.title
 * 2) Si coincide, guarda la pos [i]
 * 3) Borra env_dup[i] y genera un env_dup nuevo (malloc + free)
 * 4) Actualizamos get env_array a partir del nuevo env_dup
 * 5) Buscamos cada arg[i] (menos 0) de unset en env_exp (como?)
 * ...
 */