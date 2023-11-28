/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:15:46 by pgruz11           #+#    #+#             */
/*   Updated: 2023/11/25 11:31:41 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Misma función de fer, pero le he quitado el check de exit
para tratarlo a parte*/
void	ft_is_builtin(char **cmd_line)
{
	if (ft_strcmp(cmd_line[0], "echo") == 0)
		bi_echo(cmd_line);
	else if (ft_strcmp(cmd_line[0], "cd") == 0)
		ft_printf("Sorry, [%s] built-in not implemented yet.\n", cmd_line[0]);
	else if (ft_strcmp(cmd_line[0], "pwd") == 0)
		ft_printf("Sorry, [%s] built-in not implemented yet.\n", cmd_line[0]);
	else if (ft_strcmp(cmd_line[0], "export") == 0)
		ft_printf("Sorry, [%s] built-in not implemented yet.\n", cmd_line[0]);
	else if (ft_strcmp(cmd_line[0], "unset") == 0)
		ft_printf("Sorry, [%s] built-in not implemented yet.\n", cmd_line[0]);
	else if (ft_strcmp(cmd_line[0], "env") == 0)
		ft_printf("Sorry, [%s] built-in not implemented yet.\n", cmd_line[0]);
}

int	ft_is_biexit(char *str)
{
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}
