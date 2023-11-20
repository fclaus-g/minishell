/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/20 09:46:49 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	d;
	t_input	input;
	char	*str_input;
	//int		i;

	(void)av;
	//i = 0;
	if (ac > 1)
		return (1);
	ft_init(&d, env, &input);
	// while (d.env_arr[i].full != NULL)
	// {
	// 	ft_printf("%s\n", d.env_arr[i].full);
	// 	i++;
	// }
	while (1)
	{
		ft_clean_input(&input);
		str_input = readline("cascarabash/> ");
		add_history(str_input);
		ft_fill_input(&input, str_input);
		ft_checkinput(&input);
	}
	return (0);
}
