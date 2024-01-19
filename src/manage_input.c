/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/19 14:10:54 by pgomez-r         ###   ########.fr       */
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
