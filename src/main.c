/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/13 12:56:51 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_split_env(t_data *d, char *var, size_t x)
{
	int	i;
	int	j;

	i = 1;
	while (var[i] != '=')
		i++;
	d->env_arr[x].title = malloc(sizeof(char) * i);
	i = -1;
	while (var[++i] != '=')
		d->env_arr[x].title[i] = var[i];
	d->env_arr[x].title[i] = '\0';
	i++;
	j = i;
	while (var[i] != '\0')
		i++;
	d->env_arr[x].line = malloc(sizeof(char) * (i + 1) - j);
	i = j - 1;
	j = -1;
	while (var[++i] != '\0')
		d->env_arr[x].line[++j] = var[i];
	d->env_arr[x].line[j + 1] = '\0';
}

void	ft_init(t_data *d, char **env)
{
	size_t	i;

	d->env_dup = env;
	d->env_arr = malloc(sizeof(t_env) * ft_strdlen(d->env_dup));
	i = -1;
	while (++i < ft_strdlen(d->env_dup))
	{
		d->env_arr[i].full = ft_strdup(d->env_dup[i]);
		ft_split_env(d, env[i], i);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;
	char	*str_input;
	int		i = 0;

	(void)av;
	if (ac > 1)
		return (1);
	ft_init(&d, env);
	while (d.env_arr[i].full != NULL)
	{
		ft_printf("%s\n", d.env_arr[i].full);
		i++;
	}
	while (1)
	{
		// if (elements)
		// 	free_input;
		str_input = readline("hackershell/> ");
		add_history(str_input);
		//ft_divide_input;
		// if (built == 0)
		// 	ft_executor;
		// else
		// 	ft_built_select;
	}
	return (0);
}
