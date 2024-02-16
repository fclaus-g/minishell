/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:30:09 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/02/16 12:38:11 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*esta funcion chequeara si las comillas estan cerradas, si es asi
definira el tipo de comillas con ft_define-qtype y si hay dollar lo 
expandira LO MISMO CREO UN PUNTERO A ENV PARA TRABAJAR MAS COMODO*/
int	ft_management_quotes(t_element *element, t_data *d)
{
	if (ft_count_quotes(element->data) % 2 != 0)
	{
		d->exit_code = 1;
		printf("cascaribash: syntax error: unclosed quotes\n");
		return (1);
	}
	if (ft_closed_quotes(element->data))
	{
		element->type = ft_define_qtype(*element);
		//element->data = ft_clean_quotes(*element, d);
	}
	return (0);
}

/*funcion que chequea si las comillas estan cerradas*/
int	ft_closed_quotes(char *str)
{
	int		c;
	char	quote;
	int		quotes;

	c = -1;
	quotes = 0;
	while (str[++c])
	{
		if (ft_is_quote(str[c]))
		{
			quote = str[c];
			quotes++;
			while (str[++c])
			{
				if (str[c] == quote)
					quotes++;
			}
		}
	}
	if (quotes % 2 == 0)
		return (1);
	return (0);
}

/*funcion que devuelve el tipo de comilla que estamos tratando*/
char	ft_define_qtype(t_element element)
{
	int		c;
	char	quote;

	c = -1;
	while (element.data[++c])
	{
		if (ft_is_quote(element.data[c]))
		{
			quote = element.data[c];
			return (quote);
		}
	}
	return (0);
}

/*funcion que va a eliminar las comillas del bloque teniendo 
en cuenta que deben ser del mismo tipo (si hay comillas del otro
tipo deben mostrarse)*/
char	*ft_clean_quotes(t_element *element, t_data *d)
{
	char	*aux;
	int		c;
	int		i;

	aux = ft_calloc(sizeof(char),
			ft_strlen(element->data) - ft_count_quotes(element->data) + 1);
	if (!aux)
		return (NULL);
	c = -1;
	i = 0;
	d->q = 0;
	d->q_flag = 0;
	while (element->data[++c])
	{
		if (ft_is_quote(element->data[c]) && d->q_flag == 0)
			ft_flag_check(d, element->data[c], 0);
		else if (element->data[c] == d->q && d->q_flag == 1)
			ft_flag_check(d, element->data[c], 1);
		else
			aux[i++] = element->data[c];
	}
	free (element->data);
	return (aux);
}

int	ft_count_quotes(char *str)
{
	int		c;
	int		quotes;
	char	q;

	c = -1;
	quotes = 0;
	while (str[++c] && str[c])
	{
		if (ft_is_quote(str[c]) && str[c])
		{
			q = str[c];
			quotes++;
			while (str[++c] && str[c])
			{
				if (str[c] == q && str[c])
				{
					quotes++;
					q = '\1';
					break ;
				}
			}
		}
	}
	return (quotes);
}
