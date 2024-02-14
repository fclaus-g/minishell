/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/02/14 13:14:37 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_manage_input(t_data *d)
{
	ft_check_special_chars_right(d);
	ft_check_special_chars_left(d);
	ft_separate_quotes(d);
	d->in.sp_input = ft_split(d->rl_input, ' ');
	ft_recovery_sp(&d->in);
	d->in.n_elements = ft_strdlen(d->in.sp_input);
	ft_fill_elements(&d->in);
	if (ft_check_elements(&d->in, d->in.elements, d))
		return (1);
	return (0);
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
	in->pipes = NULL;
}

int	ft_check_elements(t_input *in, t_element *array, t_data *d)
{
	int	i;

	(void)d;
	i = -1;
	while (++i < in->n_elements)
	{
		if (ft_quote_in_data(array[i].data))
		{
			if (ft_management_quotes(&array[i], d))
				return (1);
		}
	}
	return (0);
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
			cmd->tokens[i].data = ft_expand(cmd->tokens[i].data, d);
	}
}
