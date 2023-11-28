/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:24:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/24 22:14:11 by pgruz11          ###   ########.fr       */
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
	input->cmd_n = 0;
	if (input->sp_input != NULL)
	{
		ft_totalfree(input->sp_input);
		ft_totalfree(input->cmd_tab);
		while (++i < input->n_elements)
		{
			free(input->elements[i].data);
		}
		free(input->elements);
	}
	input->n_elements = 0;
}

/*Función para liberar memoria de la struct inicial-general, que
ahora mismo solo tiene el entorno duplicado*/
void	ft_free_data(t_data *d)
{
	int	i;

	i = -1;
	while (d->env_arr[++i].full)
	{
		free(d->env_arr[i].full);
		free(d->env_arr[i].title);
		free(d->env_arr[i].line);			
	}
}
