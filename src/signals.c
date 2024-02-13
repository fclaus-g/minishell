/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:17:20 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/02/09 10:49:12 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sign;

void	ft_signal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGSTOP, SIG_IGN);
	}
	else 
	{
		signal(SIGINT, ft_cmd_sig);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGSTOP, SIG_IGN);
	}

}

void	ft_cmd_sig(int sig)
{
	(void)sig;
	write(1, "\n", 14);
	//exit (130);
}

void	ft_here_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  ", 1);
		ft_putstr_fd("\n", 1);
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
		exit(0);
	}
}
