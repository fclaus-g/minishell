/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_spchars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:47:26 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/13 22:37:41 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Cambiar ft_token_pipes en lexer por esta ft_token_spchars
Comprobar si funciona todo igual y además guarda los nuevos tipos
Para redirecciones no me funciona porque hay que comprobar si hay una,
dos o más, se queda su función como estaba*/

void	ft_token_spchars(t_input *in)
{
	int		i;
	int		j;
	char	*set;

	set = "|;\\\0";
	j = -1;
	while (set[++j] != '\0')
	{
		i = -1;
		while (++i < in->n_elements)
		{
			if (in->elements[i].type == '0'
				&& ft_strchr(in->elements[i].data, set[j]))
			{
				if (ft_strlen(in->elements[i].data) > 1)
					in->elements = ft_arr_update(in, i, set[j]);
				else
					in->elements[i].type = set[j];
			}
		}
	}
}

int	ft_char_pos(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

/*Comprobar como se comporta con un varias cantidades de && seguidos
& && &&& &&&&&& &&&&*/

void	ft_token_and(t_input *in)
{
	int	i;
	int	and;

	i = -1;
	while (++i < in->n_elements)
	{
		and = ft_char_pos(in->elements[i].data, '&');
		if (in->elements[i].type == '0' && and >= 0)
		{
			if (in->elements[i].data[and] == in->elements[i].data[and + 1]
				&& in->elements[i].data[and] != in->elements[i].data[and + 2])
				in->elements = ft_db_redirs(in, i, in->elements[i].data[and]);
		}
	}
}

/*He modificado ft_tag_redir para que funcione con && también,
hay que comprobar que no me haya cargado su funcionamiento anterior*/