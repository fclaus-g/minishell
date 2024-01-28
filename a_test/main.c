/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/28 20:03:15 by pgruz11          ###   ########.fr       */
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
	// if (ft_is_biexit(str_input))
	// 	return (printf("Taluego\n"), 1);
	if (ft_lexer(&d))
		return (1);
	ft_cmd_maker(&d.in);
	//debug_arr(&d.in, str_input, "RESULTADO FINAL DE FT_LEXER");
	//debug_cmds(&d.in, str_input, "RESULTADO FINAL DE FT_CMD_MAKER");
	ft_cmd_driver(&d, d.in.cmds);
	return (0);
}

/**
 * TODO: para poder ejecutar, crear comandos + adaptar exeguttor
 * TODO: ft_fill_input dentro input_lexer, luego change for quote_fix
 * TODO: despues de fill_input - check_pipe
 * TODO: aqui una impresión en pantalla para comprobar, luego cmd_interp
 * TODO: cmd_interpreter - cmd_assambler.. antes o dentro de cmd_driver?
 */