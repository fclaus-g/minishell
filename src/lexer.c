/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:40:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/09 16:03:20 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Función para catalogar los archivos IN/OUT, solo cataloga, luego veremos como
gestionar los fds para redireccionar stdin/stdout*/
void	ft_token_files(t_input *in)
{
	int	i;

	i = -1;
	while (++i < in->n_elements)
	{
		if (in->elements[i].type == '<' && in->elements[i + 1].type == '0'
			&& i + 1 < in->n_elements)
			in->elements[i + 1].type = 'i';
		else if (in->elements[i].type == 'h' && i + 1 < in->n_elements)
		{
			if (in->elements[i + 1].type == '0'
				|| in->elements[i + 1].type == '\"')
				in->elements[i + 1].type = 'E';
			else if (in->elements[i + 1].type == '\'')
				in->elements[i + 1].type = 'e';
		}
		else if (in->elements[i].type == '>' && in->elements[i + 1].type == '0'
			&& i + 1 < in->n_elements)
			in->elements[i + 1].type = 'o';
		else if (in->elements[i].type == 'a' && in->elements[i + 1].type == '0'
			&& i + 1 < in->n_elements)
			in->elements[i + 1].type = 'O';
	}
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

/*Proceso de lexer/token; fill_input será sustituido por la ft que separe por 
primera vez el input en elementos teniendo en cuenta el tema de las comillas,
despues de eso la idea es ir enocontrando, separando (si están pegados sin 
espacios) y catalogando otros tipos de elementos (pipes, redirs)
*/
int	ft_lexer(t_data *d)
{
	ft_manage_input(d);
	//ft_token_pipes(&d->in);
	ft_token_spchars(&d->in)
	ft_token_redirs(&d->in);
	ft_token_files(&d->in);
	if (ft_syntax_check(&d->in))
		return (1);
	return (0);
}
