/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:57:29 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/18 22:15:21 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	ft_exit_mod(char **args, t_data *d)
{
	int	exit_stat;

	exit_stat = 0;
	if (ft_is_num(args[1]))
	{
		ft_printf_error("cascaribash: exit: %s: numeric argument required\n", args[1]);
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
