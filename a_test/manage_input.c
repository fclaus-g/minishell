/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/27 22:29:56 by pgruz11          ###   ########.fr       */
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

/*Función para guardar el input que está en formato str después de readline en 
el formato de doble matrix y array de estructuras que queremos para usarlo
En el mismo bucle podemos ir llamando a la función lexer cuando la tengamos*/
void	ft_fill_input(t_input *in, char *st)
{
	int	i;

	in->sp_input = ft_split(st, ' ');
	in->n_elements = (int)ft_strdlen(in->sp_input);
	in->elements = malloc(sizeof(t_element) * in->n_elements);
	i = -1;
	while (in->sp_input[++i] != NULL)
	{
		in->elements[i].data = ft_strdup(in->sp_input[i]);
		in->elements[i].type = '0';
	}
	in->cmd_n = 0;
	ft_totalfree(in->sp_input);
	in->sp_input = NULL;
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
