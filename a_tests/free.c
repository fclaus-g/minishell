/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:24:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/08 18:29:33 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Archivo para funciones de final de programa y liberación de memoria*/

#include "../inc/minishell.h"

/*Se llama antes de cada readline; en la primera ocasión inicia valores a 0
En el resto además libera las variables que han necesitado malloc en la lectura
anterior*/
void	ft_clean_input(t_input *input)
{
	//int	i;

	ft_free_arr(input, input->n_elements);
	// if (input->cmd_n > 0)
	// {
	// 	i = -1;
	// 	while (++i < input->cmd_n)
	// 	{
	// 		free(input->cmds->tokens[i].data);
	// 	}
	// 	free(input->cmds->tokens);
	// }
	input->cmd_n = 0;
	input->n_elements = 0;
}
/**
 * TODO: Check si se están liberando en exeguttor los char** de cms
 * Tendrían que liberarse y dejar a NULL cada vez que se termina una exe,
 * para luego volver a hacerles malloc y darles valor si es necesario en
 * siguientes comandos
 */

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

void	ft_free_arr(t_input *in, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(in->elements[i].data);
	free(in->elements);
}
