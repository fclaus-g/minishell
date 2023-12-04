/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 21:39:30 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/04 23:27:14 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_token_char(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

size_t	ft_count_elements(char *str, char c)
{
	int		i;
	size_t	cnt;

	i = -1;
	cnt = 1;
	while (str[++i] != '\0')
	{
		while (str[i] != c && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			cnt++;
		if (str[i + 1] != '\0')
			cnt++;
	}
	return (cnt);
}

char	**ft_element_split(char *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	tab = malloc(sizeof(char *) * (ft_count_elements(str, c) + 1));
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		j = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (i > j)
			tab[k++] = ft_savewords(str + j, i - j);
		if (str[i] == c)
		{
			tab[k++] = ft_token_char(c);
			i++;
		}
	}
	tab[k] = NULL;
	return (tab);
}

/*Esta función rellena el array nuevo de elementos, usamos un contador para
movernos en el array nuevo, otro para movernos en el antiguo y otro solo
para recorrer la tabla de cadenas a copiar cuando encontremos el punto 
donde insertar los elementos nuevos
Mientras no estemos en el punto a insertar (target) copiamos en el nuevo
los datos y tipo del elemento correspondiente del array original; cuando
lleguemos al target, copiamos al campo data de los nuevo elementos cada
str de tab y asignamos los type a NULL (si no funciona con varible char,
pondremos un char tipo 'X' o cualquier identificador para saber que no tiene
tipo todavía)
Tengo que comprobar bien si no me estoy equivocando con los contadores, lo
he reducido mucho para las 25 lineas y no estoy seguro de que esté bien
planteado ya, pero en su momento funcionó*/
void	ft_fill_arr(t_input *in, t_element *new_arr, int tar, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < in->n_elements)
	{
		if (i == tar)
		{
			k++;
			j = -1;
			while (tab[++j] != NULL)
			{
				new_arr[i].data = ft_strdup(tab[j]);
				new_arr[i++].type = NULL;
			}
		}
		else
		{
			new_arr[i].data = ft_strdup(in->elements[k].data);
			new_arr[i++].type = in->elements[k++].type;
		}
	}
}

void	ft_tag_type(t_element *arr, int start, char c)
{
	
}

/*Llamar a la función cuando haga falta dividir y añadir elementos, con un if 
o funcion check antes en cada ft_token, si solo hay que catalogar el elemento
lo hacemos fuera, si hay que separar sus partes se hace aquí y se cataloga la
que estamos buscando, el resto queda indefinida*/
t_element	*ft_arr_update(t_input *in, int i, char c)
{
	char		**new_text;
	t_element	*new_arr;
	int			new_size;

	new_text = ft_element_split(in->elements[i].data, c);
	new_size = in->n_elements + (int)ft_strdlen(new_text) - 1;
	new_arr = malloc(sizeof(t_element) * new_size);
	in->n_elements = new_size;
	ft_fill_arr(in, new_arr, i, new_text);
	ft_tag_type(new_arr, i, c);
	ft_totalfree(new_text);
	ft_free_arr(in);
	return (new_arr);
}
/*
int	main(void)
{
	char	*str;
	char	**test;

	str = "hello|cabesa|wordl|||yestoque";
	test = ft_element_split(str, '|');
	ft_print_dstr(test);
	return (0);
}
*/