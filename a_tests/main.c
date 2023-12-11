/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/11 21:03:34 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	debug_arr(t_input *in, char *str_in, char *msg)
{
	int	i;

	printf("///INPUT_LINE\\\\\\\n%s\n\n", str_in);
	printf("///%s\\\\\\\n\n", msg);
	printf("Número elementos actual: %d\n", in->n_elements);
	i = -1;
	while (++i < in->n_elements)
	{
		printf("Texto elemento[%d]: %s <---> ", i, in->elements[i].data);
		printf("Tipo elemento[%d]: %c\n", i, in->elements[i].type);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;
	char	*str_input;

	// str_input = NULL;
	(void)env;
	if (ac > 2)
		return (1);
	str_input = av[1];
	// ft_init(&d, env);
	// if (str_input != NULL)
	// 	ft_clean_input(&d.in);
	// str_input = readline("cascaribash/> ");
	// add_history(str_input);
	// if (ft_is_biexit(str_input))
	// 	return (printf("Taluego\n"), 1);
	ft_lexer(&d, str_input);
	debug_arr(&d.in, str_input, "RESULTADO FINAL DE FT_LEXER");
	//ft_cmd_driver(&d.in, d.env_dup, &d);
	return (0);
}

/**
 * TODO: para poder ejecutar, crear comandos + adaptar exeguttor
 * TODO: ft_fill_input dentro input_lexer, luego change for quote_fix
 * TODO: despues de fill_input - check_pipe
 * TODO: aqui una impresión en pantalla para comprobar, luego cmd_interp
 * TODO: cmd_interpreter - cmd_assambler.. antes o dentro de cmd_driver?
 */