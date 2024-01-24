/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:17:20 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/24 14:47:23 by fclaus-g         ###   ########.fr       */
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
		(void)sig;
		rl_redisplay();
		rl_replace_line("   ", 0);
		ft_putstr_fd("\n", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n"); // 0 es STDIN_FILENO
		rl_on_new_line();
}
/*no imprime bien cuando se hace ctrl D 0 comprension de lo que pasa en la funcion*/