/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/13 19:41:06 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	d;

	if (ac != 2)
		return (1);
	ft_init(&d, env);
	d.rl_input = (av[1]);
	// if (str_input != NULL)
	// 	ft_clean_input(&d.in);
	// str_input = readline("cascaribash/> ");
	// add_history(str_input);
	if (ft_lexer(&d))
		return (1);
	ft_cmd_maker(&d.in);
	//debug_arr(&d.in, d.rl_input, "RESULTADO FINAL DE FT_LEXER");
	//debug_cmds(&d.in, d.rl_input, "RESULTADO FINAL DE FT_CMD_MAKER");
	ft_cmd_driver(&d, d.in.cmds);
	ft_clean_exit(&d);
	return (0);
}
