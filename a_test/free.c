/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:24:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/14 18:35:41 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Archivo para funciones de final de programa y liberación de memoria*/

#include "../inc/minishell.h"

/*Se llama antes de cada readline; en la primera ocasión inicia valores a 0
En el resto además libera las variables que han necesitado malloc en la lectura
anterior*/
void	ft_clean_input(t_input *input)
{
	ft_free_arr(input, input->n_elements);
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
	size_t	i;

	i = -1;
	while (++i < ft_strdlen(d->env_dup))
	{
		free(d->env_arr[i].full);
		free(d->env_arr[i].title);
		free(d->env_arr[i].line);
	}
	free(d->env_arr);
}

void	ft_free_arr(t_input *in, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(in->elements[i].data);
}

/*Función para liberar toda la memoría alojada cuando se haga exit del
programa*/
void	ft_clean_exit(t_data *d, char *readline)
{
	ft_free_data(d);
	if (&d->in.n_elements > 0)
		ft_clean_input(&d->in);
	if (readline != NULL)
		free(readline);
	free(d->in.elements);
}
/**
 * TODO: mejorar el IF (comprobación) para liberar o no
 */
