/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:58:04 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/14 16:43:00 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**funcion que va a chequear cada str de la matriz comprobando una serie de cosas
para ir guardando en el array de elements el tipo de element, su contenido esta
guardado con la funcion fill_input en base al split por espacios, osea cada str 
de la matriz es ya un elemento type '0'.
el orden de comprobacion es importante y creo que lo ideal seria el suguiente:
* ? 1. comprobar si es comillas, si hay comillas aqui es donde habria que gestionarlas
lanzando un error si son impares y borrando las del mimsmo tipo (si hay simples 
dentro de dobles deben de aparecer)y sustituir si hay variables de entorno.
Para ello una funcion debera borrar $TEXT y sustituirlo por el contenido de la
variable entiendo que concatenando con el resto de la string.
* ? 2. comprobar si es una variable de entorno, si lo es sustituirla por su contenido
* ? 3. comprobar si es un built-in, si lo es cambiar el type a 'b'
* ? 4. comprobar si es una redireccion, si lo es cambiar el type a '1' '2' '3' o '4'
* ? 5. comprobar si es un pipe, si lo es cambiar el type a 'p'
* ? 6. comprobar si es un file, si lo es cambiar el type a 'f' (intentando abrirlo
si no se puede serà un cmd)
* ? 7. comprobar si es un cmd, si lo es cambiar el type a 'c'
* ? 8. comprobar si es un flag, si lo es cambiar el type a 'x'
*/ 

void	ft_checkinput(t_input *input)
{
	int i;

	i = 0;
	printf("n_elements: %d\n", input->n_elements);
	while (input->element[i].data)
	{
		ft_check_prequotes(&input->element[i], input);
		ft_check_quotes(&input->element[i]);

		i++;
	}
}
/**En esta funcion vamos a hacer todo el proceso relacionado con las comillas,
* ? 1 chequear si hay comillas y la primera que encuentre será el tipo que marcará el bloque
* ? 2 chequear si hay algo unido a las comillas y si es un pipe o redireccion y aislarlo si lo es.
* ? 3 chequear si hay comillas del mismo tipo en el resto de la string y si las hay borrarlas
* ? 4 chequear si hay variables de entorno y sustituirlas por su contenido
*/

void	ft_check_quotes(t_element *element)
{
	ft_find_quotes(element);
	ft_space_quotes(element);

}
void	ft_find_quotes(t_element *element)
{
	int c;

	c = -1;
	while (element->data[++c] && element->data[c])
	{
		if (element->data[c] == '\'')
		{
			element->type = '\'';
			printf("type: %c\n", element->type);
			break;
		}
		else if (element->data[c] == '\"')
		{
			element->type = '\"';
			printf("type: %c\n", element->type);
			break;
		}
		else
			element->type = 'c';	
	}
}
/* Esta funcion checkea si hay un caracter especial antes de las comillas y si 
lo hay la idea es dejar el caracter en ese elemento y guardar el resto en el elemento
siguiente, para ello hay que reconstruir el array con el nuevo elemento.*/
void	ft_check_prequotes(t_element *element, t_input *input)
{
	int c;

	c = -1;
	printf("cheking prequotes\n");
	while (element->data[++c] && element->data[c])
	{
		if ((element->data[c] == '\"' || element->data[c] == '\'') && c > 0)
		{
			printf("found quotes\n");
			while (c-- >= 0)
			{
				printf("c: %d\n", c);
				if (ft_is_special_char(element->data[c]))
				{
					printf("found special char//posicion de c: %d,\n", c);
					input->element = aislar_special(input, element, c);
				}
			}
		}
		
	}
}

void ft_space_quotes(t_element *element)
{
	int i;

	i = -1;
	while (element->data[++i] && element->data[i])
	{
		if (element->data[i] == '\1')
		{
			element->data[i] = ' ';
		}
	}
	printf("element->data con espacios: %s\n", element->data);
}