/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:17:20 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/02/08 14:56:43 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>

int g_sign;

void	ft_signal(void)
{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGSTOP, SIG_IGN);
}
void ft_cmd_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void ft_here_sig(int sig)
{
	(void)sig;
	g_sign = 1;
	// ft_putstr_fd("\n", 1);
	// // rl_redisplay();//se va al inicio del input y muestra ^C
	// // ft_putstr_fd("  ", 1);//escribe al inicio de la linea borrando ^C
	// ioctl(STDOUT_FILENO, TIOCSTI, " ");
}

void	ft_handler(int sig)
{
	//(void)sig;
	if (sig == SIGINT )
	{
		rl_on_new_line();//se va al inicio de la misma linea y muestr ^C
		rl_redisplay();//se va al inicio del input y muestra ^C
		ft_putstr_fd("  ", 1);//escribe al inicio de la linea borrando ^C
		ft_putstr_fd("\n", 1);//imprime el salto de linea y se va al inicio
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
		//rl_clear_history();
		exit(0); // te saca de minishell
	}
}



