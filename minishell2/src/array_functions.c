/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:58:36 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/30 17:21:48 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_print_array(t_element *array, int n_elements)
{
	int	i;

	i = 0;
	while (i < n_elements)
	{
		printf(YELLOW"element[%d].data = %s\n"RESET, i, array[i].data);
		i++;
	}
}
