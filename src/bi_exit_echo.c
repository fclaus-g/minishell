/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:57:29 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/09 12:24:00 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bi_exit(t_data *d)
{
	ft_clean_exit(d);
	exit(0);
}

void	bi_echo(t_data *d, char **args)
{
	int	i;
	int	nl;

	nl = 1;
	i = 0;
	while (args[++i] != NULL)
	{
		while (!ft_strcmp(args[i], "-n"))
		{
			nl = 0;
			i++;
		}
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ", args[i]);
	}
	if (nl == 1)
		ft_printf("\n");
	d->exit_code = 0;
}

int	ft_is_dir(t_data *d, char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir == NULL)
	{
		ft_error(d, errno, NULL);
		return (perror("cascaribash"), 1);
	}
	closedir(dir);
	return (0);
}
