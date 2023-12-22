/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:40:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/22 14:59:22 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Comprueba si hay dos elementos del mismo tipo "especial" (redirecciones y 
pipes) seguidas, si es así envía error de syntax por consola*/
int	ft_syntax_check(t_input *in)
{
	int		i;
	int		j;
	char	*set;

	set = "|<>ha";
	i = -1;
	while (set[++i] != '\0')
	{
		j = -1;
		while (++j < in->n_elements)
		{
			if (in->elements[j].type == set[i]
				&& in->elements[j + 1].type == set[i])
				return (ft_syntax_error(set[i]), 1);
		}
	}
	return (0);
}
/**
 * TODO: plantear cómo encontrar syntax error con elementos de diferente tipo >|
 * TODO: con >> o <<, cuando imprimir error near `>' o near `>>'
 */

void	ft_token_redirs(t_input *in)
{
	int	i;
	int	red;

	i = -1;
	while (++i < in->n_elements)
	{
		red = ft_is_red(in->elements[i].data);
		if (in->elements[i].type == '0' && red >= 0)
		{
			if (in->elements[i].data[red] == in->elements[i].data[red + 1]
				&& in->elements[i].data[red] != in->elements[i].data[red + 2])
				in->elements = ft_db_redirs(in, i, in->elements[i].data[red]);
			else if (ft_strlen(in->elements[i].data) > 1)
				in->elements = ft_arr_update(in, i, in->elements[i].data[red]);
			else
				in->elements[i].type = in->elements[i].data[red];
		}
	}
}

void	ft_token_pipes(t_input *in)
{
	int	i;

	i = -1;
	while (++i < in->n_elements)
	{
		if (in->elements[i].type == '0' && ft_strchr(in->elements[i].data, '|'))
		{
			if (ft_strlen(in->elements[i].data) > 1)
				in->elements = ft_arr_update(in, i, '|');
			else
				in->elements[i].type = '|';
		}
	}
}

/*Proceso de lexer/token; fill_input será sustituido por la ft que separe por 
primera vez el input en elementos teniendo en cuenta el tema de las comillas,
despues de eso la idea es ir enocontrando, separando (si están pegados sin 
espacios) y catalogando otros tipos de elementos (pipes, redirs)
*/
int	ft_lexer(t_data *d, char *str_in)
{
	ft_fill_input(&d->in, str_in);
	ft_token_pipes(&d->in);
	ft_token_redirs(&d->in);
	if (ft_syntax_check(&d->in))
		return (1);
	return (0);
}
