/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:15:46 by pgruz11           #+#    #+#             */
/*   Updated: 2024/01/16 21:15:51 by pgruz11          ###   ########.fr       */
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
