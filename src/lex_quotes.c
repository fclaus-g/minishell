/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:33:10 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/01 18:00:45 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*ft para comprobar si un char coincide con algun separador, así acortamos
los while/if y ahorramos líneas*/
int	ft_check_spc(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

/*ft para evaluar el estado de la flag de comillas, la idea es mejorar la
función para tener en cuenta también si se trata de comilla que no cierra
que esta dentro de otras, impares, etc...no se me ocurre como de momento
Devuelve la flag actualizada*/
int	ft_quote_eval(char c, int in_qt)
{
	if (c == '"' || c == '\'')
		in_qt *= -1;
	return (in_qt);
}

/*ft para checkear si la str solo contiene espacios o separadores*/
int	ft_emptystr_check(char *str)
{
	int	i;

	if (str == NULL || *str == '\0')
		return (1);
	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_check_spc(str[i]))
			return (0);
	}
	return (1);
}

/**
 * @brief Función para contar los elementos teniendo en cuenta las comillas
 * Muy larga pero funciona, la comprobación de cadena vací o que solo contenga
	separadores se puede encapsular en una función a parte (líneas 24-34)
 * TODO: hacer que contemple bien el caso  "gr"ep" como un solo element!
 * TODO: estoy tratando " y ' igual, quizá hay que separarlo ("gre'p")
 */
size_t	ft_wordcnt_qt(char *str)
{
	int	i;
	int	cnt;
	int	in_qt;

	if (ft_emptystr_check(str))
		return (0);
	cnt = 0;
	i = -1;
	in_qt = -1;
	while (str[++i] != '\0')
	{
		while (ft_check_spc(str[i]) && str[i] != '\0')
			i++;
		cnt++;
		in_qt = ft_quote_eval(str[i], in_qt);
		if (in_qt == -1)
		{
			while (!ft_check_spc(str[i]) && str[i] != '\0')
				i++;
		}
		else
		{
			i++;
			while (in_qt == ft_quote_eval(str[i], in_qt) && str[i] != '\0')
				i++;
		}
	}
	return (cnt);
}

/*versión de split que deja la str de origen dividida por espacios pero
teniendo en cuenta las comillas*/
void	ft_split_qt(char *str, t_input *in)
{
	int				i;
	int				j;
	int				k;
	int				in_qt;

	i = 0;
	k = 0;
	in_qt = -1;
	while (str[i] != '\0')
	{
		while (ft_check_spc(str[i]) && str[i] != '\0')
			i++;
		j = i;
		in_qt = ft_quote_eval(str[i], in_qt);
		if (in_qt == -1)
		{
			while (!ft_check_spc(str[i]) && str[i] != '\0')
				i++;
			if (i > j)
			{
				in->elements[k].data = ft_savewords(str + j, i - j);
				k++;
			}
		}
		else
		{
			i++;
			while (in_qt == ft_quote_eval(str[i], in_qt) && str[i] != '\0')
				i++;
			i++;
			if (i > j)
			{
				in->elements[k].data = ft_savewords(str + j, i - j);
				k++;
			}
		}
	}
}
