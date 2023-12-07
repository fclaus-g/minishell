/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:40:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/07 14:32:52 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_token_char(t_input *in, char c)
{
	int	i;

	i = 0;
	while (++i < in->n_elements)
	{
		if (in->elements[i].type == '0' && ft_strchr(in->elements[i].data, c))
		{
			if (ft_strlen(in->elements[i].data) > 1)
				in->elements = ft_arr_update(in, i, c);
			else
				in->elements[i].type = c;
		}
	}
}

void	ft_lexer(t_data *d, char *str_in)
{
	char	*set;
	int		i;

	i = -1;
	set = "|<>";
	ft_fill_input(&d->in, str_in);
	while (set[++i])
		ft_token_char(&d->in, set[i]);
}
