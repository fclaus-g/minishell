/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 07:32:32 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/23 17:29:23 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init_pipes(t_input *in)
{
	int	i;

	in->pipes = malloc(sizeof(*in->pipes) * (in->cmd_n - 1));
	if (!in->pipes)
		ft_printf_error("cascaribash: malloc error\n");
	i = -1;
	while (++i < in->cmd_n - 1)
	{
		if (pipe(in->pipes[i]) == -1)
			ft_printf_error("cascaribash: pipe error\n");
	}
}

void	ft_split_env(t_data *d, char *var, size_t x)
{
	int	i;
	int	j;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	d->env_arr[x].title = malloc(sizeof(char) * i + 1);
	i = 0;
	while (var[i] != '=' && var[i] != '\0')
	{
		d->env_arr[x].title[i] = var[i];
		i++;
	}
	d->env_arr[x].title[i] = '\0';
	i++;
	j = i;
	while (var[i] != '\0')
		i++;
	d->env_arr[x].line = malloc(sizeof(char) * ((i - j) + 1));
	i = j;
	j = 0;
	while (var[i] != '\0')
		d->env_arr[x].line[j++] = var[i++];
	d->env_arr[x].line[j] = '\0';
}

void	ft_parse_env(t_data *d, char **env)
{
	int	i;

	d->env_dup = malloc(sizeof(char *) * (int)ft_strdlen(env) + 1);
	d->env_exp = malloc(sizeof(char *) * (int)ft_strdlen(env) + 1);
	i = -1;
	while (env[++i] != NULL)
	{
		d->env_dup[i] = ft_strdup(env[i]);
		d->env_exp[i] = ft_export_varcopy(env[i]);
	}
	d->env_dup[i] = NULL;
	d->env_exp[i] = NULL;
	d->env_exp = ft_export_order(d->env_exp);
}

void	ft_get_envarray(t_data *d)
{
	int		i;

	if (d->env_arr != NULL)
	{
		i = -1;
		while (++i < d->env_size)
		{
			free(d->env_arr[i].full);
			free(d->env_arr[i].title);
			free(d->env_arr[i].line);
		}
		free(d->env_arr);
	}
	d->env_arr = malloc(sizeof(t_env) * ft_strdlen(d->env_dup));
	i = -1;
	while (++i < (int)ft_strdlen(d->env_dup))
	{
		d->env_arr[i].full = ft_strdup(d->env_dup[i]);
		ft_split_env(d, d->env_dup[i], i);
	}
	d->env_size = i;
}

void	ft_init(t_data *d, char **env)
{
	d->rl_input = NULL;
	d->env_arr = NULL;
	d->exit_code = 0;
	d->in.dptr = d;
	d->in.cmd_n = 0;
	d->in.n_elements = 0;
	d->in.pipes = NULL;
	ft_parse_env(d, env);
	ft_get_envarray(d);
}
