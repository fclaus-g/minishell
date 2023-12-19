/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:58:36 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/19 14:56:47 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_print_array(t_element *array)
{
	int	i;

	i = -1;
	while (++i < array->pos)
		printf(YELLOW"element[%d].data = %s\n"RESET, i, array[i].data);
}
