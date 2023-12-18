/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/18 08:19:12 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

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
		while (++j < in->cmds[i].size)
		{
			printf("Data elem[%d]: %s <---> ", j, in->cmds->tokens[j].data);
			printf("Type elem[%d]: %c\n", j, in->cmds->tokens[j].type);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;
	char	*str_input;

	//atexit(ft_leaks);
	str_input = NULL;
	(void)av;
	if (ac > 1)
		return (1);
	ft_init(&d, env);
	while (1)
	{
		if (str_input != NULL)
		{
			free(str_input);
			ft_clean_input(&d.in);
		}
		str_input = readline("cascaribash/> ");
		add_history(str_input);
		if (ft_is_biexit(str_input))
			return (ft_clean_exit(&d, str_input), 0);
		if (ft_lexer(&d, str_input))
			continue ;
		debug_arr(&d.in, str_input, "RESULTADO FINAL DE FT_LEXER");
		//ft_cmd_maker()
		//ft_cmd_driver(&d.in, d.env_dup, &d);
	}
	return (0);
}

/**
 * TODO: para poder ejecutar, crear comandos + adaptar exeguttor
 * TODO: ft_fill_input dentro input_lexer, luego change for quote_fix
 * TODO: despues de fill_input - check_pipe
 * TODO: aqui una impresión en pantalla para comprobar, luego cmd_interp
 * TODO: cmd_interpreter - cmd_assambler.. antes o dentro de cmd_driver?
*/