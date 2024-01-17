/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:55:43 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/17 10:36:34 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_leaks(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_data	d;
	t_input	in;
	char	*str_in;

	(void)av;
	atexit(ft_leaks);
	if (ac > 1)
		return (1);/*aqui se puede poner un mensaje de error*/
	ft_init(&d, env, &in);
	while (1)
	{
		ft_clean_input(&in);
		str_in = readline(RED"cascaribash$ "RESET);
		add_history(str_in);
		if (ft_is_biexit(str_in))
			return (ft_clean_exit(&d, str_in), 0);
		ft_manage_input(str_in, &in);
	}
	return (0);
}
