/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/16 15:57:16 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	d;
	char	*str_input;

	// str_input = NULL;
	(void)env;
	if (ac != 2)
		return (1);
	str_input = av[1];
	ft_init(&d, env);
	// if (str_input != NULL)
	// 	ft_clean_input(&d.in);
	// str_input = readline("cascaribash/> ");
	// add_history(str_input);
	// if (ft_is_biexit(str_input))
	// 	return (printf("Taluego\n"), 1);
	if (ft_lexer(&d, str_input))
		return (1);
	ft_cmd_maker(&d.in);
	//debug_arr(&d.in, str_input, "RESULTADO FINAL DE FT_LEXER");
	//debug_cmds(&d.in, str_input, "RESULTADO FINAL DE FT_CMD_MAKER");
	printf("char *rl_input (%lu bytes)\n", sizeof(d.rl_input));
	printf("t_env *env_arr (%lu bytes)\n", sizeof(*d.env_arr));
	printf("t_env in (%lu bytes)\n", sizeof(d.in));
	printf("t_element *elements (%lu bytes)\n", sizeof(*d.in.elements));
	printf("t_command *cmds (%lu bytes)\n", sizeof(*d.in.cmds));
	printf("char **split_input (%lu bytes)\n", sizeof(*d.in.sp_input));
	printf("t_element *tokens(%lu bytes)\n", sizeof(*d.in.cmds->tokens));
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