/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:55:39 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/17 10:44:38 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_clean_exit(t_data *d, char *readline)
{
	ft_free_data(d);
	ft_free_elements(d->in);
	if (readline != NULL)
		free(readline);
}

void	ft_free_data(t_data *d)
{
	size_t	i;

	i = -1;
	while (++i < ft_strdlen(d->env_dup))
	{
		free(d->env_arr[i].full);
		free(d->env_arr[i].title);
		free(d->env_arr[i].line);
	}
	free(d->env_arr);
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

void	ft_free_elements(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->n_elements)
	{
		free(input->element[i].data);
	}
	free(input->element);
}