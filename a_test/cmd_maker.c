/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:19:48 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/18 08:38:22 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Función para calcular cuantos elementos de un tipo tenemos en la linea total 
de input. Para que podamos usarla correctamente en cmd_maker, depende de que la
comprobación previa de sintaxis funcione correctamente y "aborte" misión antes 
si hay fallos de ese tipo*/
int	ft_element_cnt(t_input	*in, char c)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = -1;
	while (++i < in->n_elements)
	{
		if (in->elements[i].type == c)
			cnt++;
	}
	return (cnt);
}

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

	in->cmd_n = ft_element_cnt(in, '|') + 1;
	in->cmds = malloc(sizeof(t_command) * in->cmd_n);
	i = 0;
	curr = 0;
	while (i < in->cmd_n)
	{
		start = curr;
		in->cmds[i].paths = NULL;
		in->cmds[i].path_cmd = NULL;
		in->cmds[i].cmd_tab = NULL;
		in->cmds[i].size = ft_cmd_size(in, &curr);
		curr++;
		in->cmds[i].tokens = malloc(sizeof(t_element) * in->cmds[i].size);
		j = -1;
		while (++j < in->cmds[i].size)
			in->cmds[i].tokens[j] = in->elements[start++];
		i++;
	}
}

/**
 * TODO: Añadir un contador de numero de elementos dentro de cada comando
 * (Probando de momento con in.cmd.size...Puede funcionar, TEST!)
 */