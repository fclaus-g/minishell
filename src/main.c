/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/04 23:25:32 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	d;
	char	*str_input;

	str_input = NULL;
	(void)av;
	if (ac > 1)
		return (1);
	ft_init(&d, env);
	while (1)
	{
		if (str_input != NULL)
			ft_clean_input(&d.in);
		str_input = readline("cascaribash/> ");
		add_history(str_input);
		ft_fill_input(&d.in, str_input);
		ft_cmd_driver(&d.in, d.env_dup, &d);
	}
	return (0);
}

/**
 * TODO: ft_fill_input cambiar por input_lexer o adaptar/fusionar ambos
 * TODO: cmd_interpreter - cmd_assambler.. antes o dentro de cmd_driver?
 */