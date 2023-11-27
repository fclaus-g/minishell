/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:54:29 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/11/27 14:47:24 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(t_input *input)
{
	char pwd[PATH_MAX];
	
	(void)input;
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
}

void ft_echo(t_input *input)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (input->sp_input[i])
	{
		while (input->sp_input[i][j])
		{
			if (input->sp_input[i][j] != '"')
				ft_putchar_fd(input->sp_input[i][j], 1);
			j++;
		}
		i++;
		j = 0;
		if (input->sp_input[i])
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
}
