/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:22:15 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/05 14:28:23 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*funcion que devuelve donde inicia las comillas teniendo en cuenta que puede haber 
caracteres antes de las comillas que deben ser incluidos por ej l"s" -la debe funcionar
con normalidad*/
int ft_start_quotes(char *str)
{
	int c;

	c = -1;
	while (str[++c])
	{
		if (str[c] == '\'' || str[c] == '\"')
		{
			while (str[c] != ' ' && c >= 0)
			{
				c--;
				printf("str[%d]: %c\n", c, str[c]);	
			}
			break;
		}	
	}
	printf("start quotes: %d\n", c);
	return (c);
}

/*vamos a contar las comillas para usarlo como limite para encontrar
el final de la string entre comillas*/
int	ft_count_quotes(char *str)
{
	int c;
	int quotes;

	c = -1;
	quotes = 0;
	while (str[++c])
	{
		if (str[c] == '\'' || str[c] == '\"')
		quotes++;		
	}
	printf("end quotes: %d\n", quotes);
	return (quotes);
}

/*funcion que devuelve la ultima posicion de la string que esta entre comillas
salvando si hay caracteres despues de la ultima comilla sin un espacio en medio*/
int ft_end_quotes(char *str)
{
	int c;
	int quotes;

	c = -1;
	quotes = ft_count_quotes(str);
	while (str[++c])
	{
		if (str[c] == '\'' || str[c] == '\"')
		{
			while (str[c] && quotes >= 0)
			{
				c++;
				if (str[c] == '\'' || str[c] == '\"')
					quotes--;
			}
			break ;
		}
	}
	while (str[c] != ' ' && str[c])
		c++;
	printf("c: %d\n", c);
	return (c);
}
