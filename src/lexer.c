/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:40:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/14 13:36:11 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_red(char	*s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
			return (i);
	}
	return (-1);
}

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

/*Proceso de lexer/token o como se diga; fill_input será sustituido por la ft_
que separe por primera vez el input en elementos teniendo en cuenta el tema de
nuestras queridas comillas, depués de eso la idea es ir enocontrando, separando
(si están pegados sin espacios) y catalogando otros elementos
El orden podría ser:
- Separar/catalogar pipes
- Separar/catalogar redirecciones
*/
void	ft_lexer(t_data *d, char *str_in)
{
	int		i;

	i = -1;
	ft_fill_input(&d->in, str_in);
	ft_token_pipes(&d->in);
	ft_token_redirs(&d->in);
}
