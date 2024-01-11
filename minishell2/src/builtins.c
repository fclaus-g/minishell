/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:55:19 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/11 13:07:43 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bi_exit(t_data *d, t_input *in)
{
	ft_clean_input(in);
	ft_free_data(d);
	exit(0);
}

int	ft_is_biexit(char *str)
{
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}
