/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:17:20 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/29 14:24:07 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>

void	ft_signal(void)
{
	struct sigaction	action;

	action.sa_handler = signal(SIGINT, ft_handler);
}

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		listen = 1;
		rl_on_new_line();//se va al inicio de la misma linea y muestr ^C
		rl_redisplay();//se va al inicio del input y muestra ^C
		ft_putstr_fd("  ", 1);//escribe al inicio de la linea borrando ^C
		printf("\n");//imprime el salto de linea y se va al inicio
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_control_d(t_data *d)
{
	if (!d->rl_input)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		exit(0); // te saca de minishell
	}
}
