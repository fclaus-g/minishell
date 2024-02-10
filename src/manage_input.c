/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/02/10 23:50:39 by pgomez-r         ###   ########.fr       */
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

void	ft_fill_elements(t_input *in)
{
	int	i;

	i = -1;
	in->elements = malloc(sizeof(t_element) * in->n_elements);
	if (!in->elements)
		printf("cascaribash: malloc error\n");
	while (++i < in->n_elements)
	{
		in->elements[i].type = '0';
		in->elements[i].data = ft_strdup(in->sp_input[i]);
	}
	in->cmd_n = 0;
	ft_totalfree(in->sp_input);
	in->sp_input = NULL;
}

void	ft_check_elements(t_input *in, t_element *array, t_data *d)
{
	int	i;

	(void)d;
	i = -1;
	while (++i < in->n_elements)
	{
		if (ft_quote_in_data(array[i].data))
			ft_management_quotes(&array[i], d);
	}
}

int	ft_its_dollar(char *str)
{
	int	c;

	c = -1;
	while (str[++c])
	{
		if (str[c] == '$')
			return (1);
	}
	return (0);
}

void	ft_dollar_check(t_command *cmd, t_data *d)
{
	int		i;
	char	c;

	i = -1;
	while (++i < cmd->size)
	{
		c = cmd->tokens[i].type;
		if ((c == '0' || c == '\"') && ft_its_dollar(cmd->tokens[i].data))
			cmd->tokens[i].data = ft_expand_hdoc(cmd->tokens[i].data, d);
	}
}

/*
10-02-24 -> Comienzo a probar sustituir todas las ft_expand que funcionan
	con t_element por las que devuelven char*
El planteamiento original es en ft_dollar_check: 
	l:78  if ((c == '0' || c == '\"') && ft_its_dollar(cmd->tokens[i].data))
			ft_expand_dollar(&cmd->tokens[i], d);
Si funciona así -> unificar las funciones hdoc y expand en uno o varios file.c
*/