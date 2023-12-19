/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:21:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/19 14:56:33 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_fill_elements(t_input *in)
{
	int	i;

	i = -1;
	in->element = malloc(sizeof(t_element) * in->n_elements);
	if (!in->element)
		printf(RED"malloc ko\n"RESET);
	printf(GREEN"malloc ok\n"RESET);
	while (++i < in->n_elements)
	{
		in->element[i].type = '0';
		in->element[i].data = ft_strdup(in->sp_input[i]);
		in->element[i].fd_in = 0;
		in->element[i].fd_out = 1;
		in->element[i].priority = 0;
		in->element[i].pos = i;
		//in->element[i].next = NULL;
	}
	ft_print_array(in->element);
}
