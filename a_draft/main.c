/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/07 21:44:36 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	ft_engine(t_data *d)
{
	char	*str_input;

	str_input = NULL;
	while (1)
	{
		if (str_input != NULL)
		{
			free(str_input);
			ft_clean_input(&d->in);
		}
		str_input = readline("cascaribash/> ");
		add_history(str_input);
		if (ft_is_biexit(str_input))
			return (ft_clean_exit(d, str_input));
		if (ft_lexer(d, str_input))
			continue ;
		ft_cmd_maker(&d->in);
		ft_cmd_driver(d->in.cmds, d->env_dup, d);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;

	atexit(ft_leaks);
	(void)av;
	if (ac > 1)
		return (1);
	ft_init(&d, env);
	ft_engine(&d);
	return (0);
}
