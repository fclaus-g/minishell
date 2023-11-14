/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:58:04 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/11/14 14:51:04 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*En esta funcion voy a tratar de chquear la matriz que contiene el input spliteado por espacios
con la intencion de clasificar los elementos en built-in, redirecciones, pipes, etc. y tratar 
de darle un orden de ejecucion a cada uno de ellos. Dentro podria incluir la funcion ft_is_builtin, ft_is_redir
ft_is_pipe lo ideal seria tambien saber diferenciar un comando de un archivo, AUN NO  SE DE QUE MANERA.
Una vez que sepa que tipo de elemento es cada uno, podria ir guardando en la estructura t_element
el tipo de elemento y su contenido en str, para luego poder ejecutarlo en el orden que corresponda.
Y a continuacion comenzar a programar los builtins, detecto a priori que desde aqui no podria a no ser que pase la struct
con el env guardado o que la linkee en la struct general data*/
void	ft_checkinput(t_data *d, t_input *input)
{
	int i;

	i = -1;
	while (input->sp_input[++i] != NULL)
}