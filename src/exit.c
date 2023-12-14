/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:24:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/12 12:16:21 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Archivo para funciones de final de programa y liberación de memoria*/

#include "../inc/minishell.h"

/*Se llama antes de cada readline; en la primera ocasión inicia valores a 0
En el resto además libera las variables que han necesitado malloc en la lectura
anterior*/
void	ft_clean_input(t_input *input)
{
	int	i;

	i = -1;
	input->is_built = 0;
	input->is_redir = 0;
	input->n_pipe = 0;
	if (input->sp_input != NULL)
	{
		ft_totalfree(input->sp_input);
		while (++i < input->n_elements)
		{
			free(input->element[i].data);
		}
		free(input->element);
	}
	input->n_elements = 0;
}
