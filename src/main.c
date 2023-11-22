/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/22 23:31:42 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	//t_data	d;
	t_input	input;
	char	*str_input;

	(void)av;
	if (ac > 1)
		return (1);
	//ft_init(&d, env);
	while (1)
	{
		ft_clean_input(&input);
		str_input = readline("cascarabash/> ");
		add_history(str_input);
		ft_fill_input(&input, str_input);
		ft_cmd_driver(&input, env);
	}
	return (0);
}
