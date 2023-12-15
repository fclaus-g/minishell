/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:19:48 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/15 13:36:39 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cmd_size(t_input *in, int *start)
{
	int	i;
	int	size;

	i = *(start);
	size = 0;
	if (in->elements[i].type == '|')
		i++;
	while (in->elements[i].type != '|' && i < in->n_elements)
	{
		size++;
		i++;
	}
	*(start) = i;
	return (size);
}

void	ft_cmd_assembler(t_input *in)
{
	int	i;
	int	j;
	int	start;
	int	curr;
	int	size;

	in->cmds = malloc(sizeof(t_command) * in->cmd_n);
	i = 0;
	curr = 0;
	while (i < in->cmd_n)
	{
		start = curr;
		in->cmds[i].paths = NULL;
		in->cmds[i].path_cmd = NULL;
		in->cmds[i].cmd_tab = NULL;
		size = ft_cmd_size(in, &curr);
		in->cmds[i] = malloc(sizeof(t_element) * size);
		j = -1;
		while (++j < size)
			in->cmds[i].tokens[j] = in->elements[start++];
		i++;
	}
}

/*Dudas que tengo ahora mismo:
-Más de un pipe? no lo gestionamos de momento ni como || (or)
	pero para que salte error de sintaxis?
-Plantear el tema de varios pipes seguidos en ft_token_pipe tambien,
	para no contar cmd++ por pipe...*/