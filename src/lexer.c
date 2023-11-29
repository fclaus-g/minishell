/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:39:07 by pgruz11           #+#    #+#             */
/*   Updated: 2023/11/29 22:44:06 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int	non_spc;

	if (str == NULL || *str == '\0')
		return (0);
	non_spc = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] != ' ' || str[i] != '\t' || str[i] != '\n' || str[i] != '\r')
			non_spc = 1;
	}
	if (!non_spc)
		return (0);
	cnt = 0;
	in_qt = -1;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
		{
			while (str[i + 1] == ' ' || str[i + 1] == '\t'
				|| str[i + 1] == '\n' || str[i + 1] == '\r')
				++i;
			if (in_qt == -1 && str[i + 1] != '\0')
				++cnt;
		}
		if ((str[i] == '"' || str[i] == '\'') && in_qt == -1)
			in_qt *= -1;
		else if ((str[i] == '"' || str[i] == '\'') && in_qt == 1)
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\n'
				|| str[i + 1] == '\r')
				in_qt *= -1;
		}
	}
	return (cnt);
}

int	main(void)
{
	int		i;

	i = (int)ft_wordcnt_qt("   hola cabesa , esta \"preba debería \"dar como\" resultado un 8\n");
	printf("El valor que devuelve wordcnt es: %d", i);
	return (0);
}
