/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:52:53 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/11/27 11:19:12 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init_structs(t_data *d, t_input *input)
{
	ft_init_data(d, input);
	ft_init_input(input);
}

void	ft_init_data(t_data *d, t_input *input)
{
	d->env_dup = NULL;
	d->env_arr = NULL;
	d->in = input;

}

void	ft_init_input(t_input *input)
{
	input->n_elements = 0;
	input->is_built = 0;
	input->is_flag = 0;
	input->is_redir = 0;
	input->n_pipe = 0;
	input->n_lines = 0;
	input->sp_input = NULL;
	input->sp_pipe = NULL;
	input->elements = NULL;
}
