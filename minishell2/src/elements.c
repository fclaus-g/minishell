/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:21:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/18 10:31:25 by fclaus-g         ###   ########.fr       */
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
	while (++i < in->n_elements)
	{
		in->element[i].type = '0';
		in->element[i].data = ft_strdup(in->sp_input[i]);
		in->element[i].fd_in = 0;
		in->element[i].fd_out = 1;
		in->element[i].priority = 0;
		in->element[i].pos = i;
		in->element[i].data_st = in->data;
		printf(BLUE"element[%d].data = %s\n"RESET, i, in->element[i].data);
	}
	//ft_print_array(in->element, in->n_elements);
}

/*en esta funcion vamos a chequear cada elemento de l array
gestionando en primer lugar si tiene comillas con la funcion
ft_management_quotes, donde comprobaremos si hay dollar y eliminaremos
las comillas necesarias, ACLARACION PARA EL FUTURO, en un array
no necesitamos añadir un puntero mas ya que un ARRAY ES UN PUNTERO
EN SI A LA PRIMERA POSICIÓN DEL ARRAY, si en alguna función vamos a
modificar el valor de un elemento del array si que necesitamos * y &, 
* en el prototipo y & en la llamada a funcion. Si no vamos a modificar
el valor del elemento en si, sino que la función chequeara valores y 
los retornará, se puede pasar en la llamada ft_funcion(*valor).*/
void	ft_check_elements(t_input *in, t_element *array)
{
	int	i;

	i = -1;
	while (++i < in->n_elements)
	{
		if (ft_quote_in_data(array[i].data))
			ft_management_quotes(&array[i]);
	}
	i = -1;
	while (++i < in->n_elements)
	{
		if (ft_its_dollar(array[i].data) && array[i].type != '\'')
			ft_expand_dollar(&array[i], in->data);
	}
}

int	ft_its_dollar(char *str)
{
	int	c;

	c = -1;
	while (str[++c])
	{
		if (str[c] == '$')
			return (1);
	}
	return (0);
}

void	ft_print_element(t_element element)
{
	printf(BLUE"element.data = %s\n"RESET, element.data);
	printf(YELLOW"element.type = %c\n"RESET, element.type);
	printf(YELLOW"element.fd_in = %d\n"RESET, element.fd_in);
	printf(YELLOW"element.fd_out = %d\n"RESET, element.fd_out);
	printf(YELLOW"element.priority = %d\n"RESET, element.priority);
	printf(YELLOW"element.pos = %d\n"RESET, element.pos);
}
