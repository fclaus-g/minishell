/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_temp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:57:29 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/18 10:46:37 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bi_exit(t_data *d)
{
	ft_clean_exit(d);
	exit(0);
}

void	bi_echo(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[++i] != NULL)
		ft_printf("%s ", cmd_line[i]);
	ft_printf("\n");
}
