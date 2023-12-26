/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/24 08:36:32 by pgruz11          ###   ########.fr       */
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

void	debug_cmds(t_input *in, char *str_in, char *msg)
{
	int	i;
	int	j;

	printf("///INPUT_LINE\\\\\\\n%s\n\n", str_in);
	printf("///%s\\\\\\\n\n", msg);
	printf("Número comandos actual: %d\n", in->cmd_n);
	i = -1;
	while (++i < in->cmd_n)
	{
		j = -1;
		printf(" --- COMMAND[%d] --- \n", i);
		printf("CMD_LINE[%d]: %s\n", i, in->cmds[i].cmd_line);
		while (++j < in->cmds[i].size)
		{
			printf("Data elem[%d]: %s <---> ", j, in->cmds[i].tokens[j].data);
			printf("Type elem[%d]: %c\n", j, in->cmds[i].tokens[j].type);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;
	char	*str_input;

	// str_input = NULL;
	(void)env;
	if (ac != 2)
		return (1);
	str_input = av[1];
	// ft_init(&d, env);
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
	ft_cmd_driver(d.in.cmds, d.env_dup, &d);
	return (0);
}

/**
 * TODO: para poder ejecutar, crear comandos + adaptar exeguttor
 * TODO: ft_fill_input dentro input_lexer, luego change for quote_fix
 * TODO: despues de fill_input - check_pipe
 * TODO: aqui una impresión en pantalla para comprobar, luego cmd_interp
 * TODO: cmd_interpreter - cmd_assambler.. antes o dentro de cmd_driver?
 */