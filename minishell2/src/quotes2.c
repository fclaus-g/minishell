/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:30:09 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/08 12:50:23 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*esta funcion chequeara si las comillas estan cerradas, si es asi
definira el tipo de comillas con ft_define-qtype y si hay dollar lo 
expandira LO MISMO CREO UN PUNTERO A ENV PARA TRABAJAR MAS COMODO*/ 
void	ft_management_quotes(t_element element)
{
	if (ft_closed_quotes(element.data))
	{
		element.type = ft_define_qtype(element);
		ft_clean_quotes(element);
	}
	else
		printf(RED"Error: unclosed quotes\n"RESET);
}

/*funcion que chequea si las comillas estan cerradas*/
int	ft_closed_quotes(char *str)
{
	int		c;
	char	quote;

	c = -1;
	while (str[++c])
	{
		if (ft_is_quote(str[c]))
		{
			quote = str[c];
			while (str[++c])
			{
				if (str[c] == quote)
					return (1);
			}
		}
	}
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
void	ft_clean_quotes(t_element element)
{
	int 	c;
	int		i;
	char	*aux;

	c = -1;
	i = 0;
	aux = ft_calloc(sizeof(char), ft_strlen(element.data) - ft_count_quotes(element.data));
	while (element.data[++c])
	{
		if (!ft_is_quote(element.data[c]))
		{
			aux[i] = element.data[c];
			i++;
		}
	}
	element.data = aux;
	ft_print_element(element);
}

int	ft_count_quotes(char *str)
{
	int		c;
	int		quotes;
	char	q;

	c = -1;
	quotes = 0;
	while (str[++c])
	{
		if (ft_is_quote(str[c]))
		{
			q = str[c];
			quotes++;
			while (str[++c])
			{
				if (str[c] == q)
				{
					quotes++;
				}
			}
		}
	}
	printf("quotes = %d\n", quotes);
	return (quotes);
}
