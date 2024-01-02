/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/31 17:05:14 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	d;
	char	*str_input;

	//atexit(ft_leaks("leaks -q minishell"));
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
		ft_cmd_maker(&d.in);
		ft_cmd_driver(d.in.cmds, d.env_dup, &d);
		//debug_cmds(&d.in, str_input, "RESULTADO ACTUAL LEXER + MAKER");
	}
	return (0);
}
