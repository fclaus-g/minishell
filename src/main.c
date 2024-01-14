/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/14 18:17:48 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_leaks(void)
{
	system("leaks -q test");
}

void	ft_engine(t_data *d)
{
	while (1)
	{
		if (d->rl_input != NULL)
		{
			free(d->rl_input);
			ft_clean_input(&d->in);
		}
		d->rl_input = readline("cascaribash/> ");
		add_history(d->rl_input);
		if (ft_lexer(d, d->rl_input))
			continue ;
		ft_cmd_maker(&d->in);
		ft_cmd_driver(d, d->in.cmds);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;

	//atexit(ft_leaks);
	(void)av;
	if (ac > 1)
		return (1);
	ft_init(&d, env);
	ft_engine(&d);
	return (0);
}
