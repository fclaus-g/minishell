/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:15:46 by pgruz11           #+#    #+#             */
/*   Updated: 2024/01/29 10:53:35 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_getenv(t_data *d, char *var)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strdlen(d->env_dup))
	{
		if (!ft_strcmp(d->env_arr[i].title, var))
			return (d->env_arr[i].line);
	}
	return (NULL);
}

int	ft_is_built(char *str)
{
	char	*builts[8];
	int		i;

	if (str != NULL)
	{
		builts[0] = "echo\0";
		builts[1] = "cd\0";
		builts[2] = "pwd\0";
		builts[3] = "export\0";
		builts[4] = "unset\0";
		builts[5] = "env\0";
		builts[6] = "exit\0";
		builts[7] = NULL;
		i = -1;
		while (++i < 7)
		{
			if (ft_strcmp(str, builts[i]) == 0)
				return (1);
		}
	}
	return (0);
}

void	ft_tag_builts(t_command *cmds, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (ft_is_built(cmds[i].cmd_tab[0]))
			cmds[i].built = 1;
	}
}

char	*ft_str_rplc(char *src, char *new)
{
	char	*aux;

	aux = ft_strdup(new);
	free (src);
	return (aux);
}

void	ft_overwrite_var(t_data *d, char *var, char* new)
{
	int	i;
	int	j;

	i = 0;
	while (ft_strncmp(d->env_dup[i], var, ft_strlen(var)))
		i++;
	d->env_dup[i] = ft_str_rplc(d->env_dup[i], new);
	j = 0;
	while (ft_strncmp(d->env_exp[j], var, ft_strlen(var)))
		j++;
	free(d->env_exp[j]);
	d->env_exp[j] = ft_export_varcopy(d->env_dup[i]);
}

/**
 * TODO: check memoria con free(d.env_exp[j]) no me convence...
 */