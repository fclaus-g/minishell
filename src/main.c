/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/13 20:00:50 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	ft_engine(t_data *d)
{
	ft_signal();
	while (1)
	{
		if (d->rl_input != NULL)
		{
			free(d->rl_input);
			ft_clean_input(&d->in);
		}
		d->rl_input = readline("cascaribash/> ");
		ft_control_d(d);
		add_history(d->rl_input);
		if (ft_lexer(d))
			continue ;
		ft_cmd_maker(&d->in);
		ft_cmd_driver(d, d->in.cmds);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;

	g_sign = 0;
	atexit(ft_leaks);
	(void)av;
	if (ac > 1)
		return (1);
	ft_init(&d, env);
	ft_engine(&d);
	return (0);
}
