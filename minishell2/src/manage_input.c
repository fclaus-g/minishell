/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/19 14:53:01 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_manage_input(char *str_in, t_input *in)
{
	in->str_input = ft_strdup(str_in);
	ft_separate_quotes(in);
	in->sp_input = ft_split(in->str_input, ' ');
	ft_print_dstr(in->sp_input);
	ft_recovery_sp(in);
	ft_print_dstr(in->sp_input);
	in->n_elements = ft_strdlen(in->sp_input);
	ft_fill_elements(in);
	
}

/*Se llama antes de cada readline; en la primera ocasión inicia valores a 0
En el resto además libera las variables que han necesitado malloc en la lectura
anterior*/
void	ft_clean_input(t_input *input)
{
	int	i;

	i = -1;
	input->is_built = 0;
	input->is_redir = 0;
	input->n_pipe = 0;
	if (input->sp_input != NULL)
	{
		ft_totalfree(input->sp_input);
		while (++i < input->n_elements)
		{
			free(input->element[i].data);
		}
		free(input->element);
	}
	input->n_elements = 0;
}


/* ************************************************************************** */