/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:57:29 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/28 15:41:31 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bi_env(char **args, t_data *d)
{
	if (ft_strdlen(args) > 1)
	{
		if (ft_strdlen(args) == 2 && !ft_strcmp(args[1], "-"))
			d->exit_code = 0;
		else if (args[1][0] == '-' && args[1][1])
		{
			ft_printf_error("cascaribash: env: illegal option -- %c\n",
				args[1][0]);
			d->exit_code = 1;
		}
		else
		{
			ft_printf_error("cascaribash: env: %s: No such file or directory\n",
				args[1]);
			d->exit_code = 127;
		}
	}
	else
	{
		ft_print_dstr(d->env_dup);
		d->exit_code = 0;
	}
}

void	ft_exit_mod(char **args, t_data *d)
{
	int	exit_stat;

	exit_stat = 0;
	if (ft_is_num(args[1]))
	{
		ft_printf_error("cascaribash: exit: %s: numeric argument required\n",
			args[1]);
		ft_clean_exit(d);
		exit(255);
	}
	if (!ft_is_num(args[1]) && ft_strdlen(args) == 2)
	{
		exit_stat = ft_atoi(args[1]);
		ft_printf("exit\n");
		ft_clean_exit(d);
		exit(exit_stat);
	}
	if (!ft_is_num(args[1]) && ft_strdlen(args) > 2)
	{
		d->exit_code = 1;
		ft_printf_error("cascaribash: exit: too many arguments\n");
		return ;
	}
}

void	bi_exit(char **args, t_data *d)
{
	if (ft_strdlen(args) > 1)
		ft_exit_mod(args, d);
	else
	{
		ft_clean_exit(d);
		ft_printf("exit\n");
		exit(0);
	}
}

void	bi_echo(t_data *d, char **args)
{
	int	i;
	int	nl;
	int	len;

	len = ft_strdlen(args);
	nl = 1;
	i = 0;
	while (++i < len && !ft_strcmp(args[i], "-n"))
		nl = 0;
	while (i < len)
	{
		ft_printf("%s", args[i]);
		if (i + 1 < len)
			ft_printf(" ", args[i]);
		i++;
	}
	if (nl == 1)
		ft_printf("\n");
	d->exit_code = 0;
}
