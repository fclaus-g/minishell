/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funciones_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:10:38 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/14 16:40:14 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*en esta funcion intento solucionar un problema que me ha surgido, en algun momento
habra que añadir un elemento al array de elementos. Para ello, se crea un nuevo array
de elementos, se copian los elementos del array original y se añade el nuevo elemento
en la posicion que se quiera. si quieres ponerlo en una posicion concreta con el int pos 
te permite hacerlo, si quieres añadirlo al final pos = -1.*/
t_element *add_element_array(t_input *in, char *add, int pos)
{
	t_element *new;
	int c;

	c = -1;
	new = malloc(sizeof(t_element) * (in->n_elements + 1));
	while (in->element[c].data)
	{	
		if (pos > 0)
		{
			while (++c < pos)
			{
				new[c].data = ft_strdup(in->element[c].data);
				printf("new[%d].data = %s\n", c, new[c].data);
			}
			new[c].data = ft_strdup(add);
			printf("new[%d].data = %s\n", c, new[c].data);
			while (in[++c].data)
			{
				new[c].data = ft_strdup(in->element[c].data);
				printf("new[%d].data = %s\n", c, new[c].data);
			}	
		}
		else 
		{
			while (in[++c].data)
			{
				new[c].data = ft_strdup(in->element[c].data);
			}
			new[c].data = ft_strdup(add);
		}
	}
	return (free(in->element), new);
}
/*funcion que pretende dejar guardado lo que hay en el elemento hasta la posicion pos
y guardar a partir de pos en un nuevo elemento*/
t_element *aislar_special(t_input *in,t_element *elemento, int pos)
{
	t_element *new;
	char 	*aux;
	char	*aux2;
	int c;
	
	c = 0;
	new = malloc(sizeof(t_element) * (in->n_elements + 1));
	if (pos >= 0)
	{
		aux = ft_substr(elemento->data, 0, pos + 1);
		aux2 = ft_substr(elemento->data, pos + 1, ft_strlen(elemento->data));
		printf("aux = %s aux2 = %s\n", aux, aux2);
		while (in->element[c].data)
		{
			//new[c].data = ft_strdup(in->element[c].data);
			printf("new[c].data = %s\n", new[c].data);
			printf("elemento->pos = %d\n", elemento->pos);
			if (c == elemento->pos)
			{
			 	printf("valor de c = %d\n", c);
				new[c].data = ft_strdup(aux);
			 	new[c++].data = ft_strdup(aux2);
			}
			new[c].data = ft_strdup(in->element[c].data);
			c++;
		}
	}
	ft_printarray(new);
	return (new);
}

int ft_is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

void	ft_printarray(t_element *array)
{
	int i;

	i = -1;
	while (array[++i].data)
		printf("element[%d].data = %s\n", i, array[i].data);
}

