/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/19 23:09:47 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_manage_input(t_data *d)
{
	ft_separate_quotes(d);
	d->in.sp_input = ft_split(d->rl_input, ' ');
	ft_recovery_sp(&d->in);
	d->in.n_elements = ft_strdlen(d->in.sp_input);
	ft_fill_elements(&d->in);
	ft_check_elements(&d->in, d->in.elements, d);
}

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}
