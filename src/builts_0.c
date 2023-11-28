/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:57:29 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/24 23:46:29 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bi_exit(t_data *d, t_input *in)
{
	ft_clean_input(in);
	ft_free_data(d);
	exit(0);
}

void	bi_echo(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[++i] != NULL)
		ft_printf("%s ", cmd_line[i]);
	ft_printf("\n");
	exit(0);
}
