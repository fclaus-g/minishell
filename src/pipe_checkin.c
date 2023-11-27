/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checkin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:37:54 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/11/26 18:00:12 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*en esta funcion vamos a checkear la matriz con el contenido encontrado entre los pipes 
y a detectar de que tipo es cada cosa, creo que asi sera mas facil quitar comillas*/
void	ft_pipe_checkinput(t_input *input)
{
	int i;
}


void	ft_print_matriz(char **matriz)
{
	int i;

	i = 0;
	while (matriz[i])
	{
		printf("matriz[%d]: %s\n", i, matriz[i]);
		i++;
	}
}