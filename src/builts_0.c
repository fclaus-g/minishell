/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:57:29 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/01 17:29:11 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bi_exit(t_data *d, t_input *in)
{
	ft_clean_input(in);
	ft_free_data(d);
	exit(0);
}

void	bi_echo(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[++i] != NULL)
		ft_printf("%s ", cmd_line[i]);
	ft_printf("\n");
	exit(0);
}

void	bi_env(t_data *d)
{
	int	i;

	i = 0;
	while (d->env_dup[i])
	{
		printf("%s\n", d->env_dup[i]);
		i++;
	}
}

void	bi_export(t_data *d)
{
	char	**temp;
	int		i;

	i = -1;
	temp = ft_export_order(d->env_dup);
	while (temp[++i])
		printf("%s\n", temp[i]);
}

char	**ft_export_order(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

void	ft_pwd(t_data *d)
{
	char	pwd[PATH_MAX];

	(void)d;
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
}
