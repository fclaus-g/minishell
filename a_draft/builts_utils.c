/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:15:46 by pgruz11           #+#    #+#             */
/*   Updated: 2024/01/13 01:15:07 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Misma función de fer, pero le he quitado el check de exit
para tratarlo a parte*/
int	ft_is_builtin(char **cmd_line)
{
	if (ft_strcmp(cmd_line[0], "echo") == 0)
		bi_echo(cmd_line);
	else if (ft_strcmp(cmd_line[0], "cd") == 0)
		return (ft_printf("[%s] built not implemented yet.\n", cmd_line[0]), 0);
	else if (ft_strcmp(cmd_line[0], "pwd") == 0)
		return (ft_printf("[%s] built not implemented yet.\n", cmd_line[0]), 0);
	else if (ft_strcmp(cmd_line[0], "export") == 0)
		return (ft_printf("[%s] built not implemented yet.\n", cmd_line[0]), 0);
	else if (ft_strcmp(cmd_line[0], "unset") == 0)
		return (ft_printf("[%s] built not implemented yet.\n", cmd_line[0]), 0);
	else if (ft_strcmp(cmd_line[0], "env") == 0)
		return (ft_printf("[%s] built not implemented yet.\n", cmd_line[0]), 0);
	return (1);
}

int	ft_is_biexit(char *str)
{
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}
