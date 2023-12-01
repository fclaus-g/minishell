/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/01 18:43:24 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	d;
	char	*str_input = NULL;

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
		//ft_input_lexer(&d, str_input); CAMBIAR fill_input por lexer
		//ft_cmd_interprer(&d); //ya teniendo comandos listos, interpretar si hay que hacer redirecciones, crear/abrir archivos, etc
		ft_cmd_driver(&d.in, d.env_dup, &d);
	}
	return (0);
}
