/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:34:04 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/20 12:46:59 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*En ft_separate_quotes vamos a usar un caracter de control '\1' para 
cambiarlo por cada espacio que nos encontremos dentro de las comillas 
con la idea de hacer luego un split y las comillas se queden en una linea
de la matriz, a posteriori volveremos a cambiar el '\1' por ' '*/
void	ft_separate_quotes(t_input *in)
{
	int		c;
	int		flag;
	char	q;

	c = 0;
	flag = -1;
	while (in->str_input[c])
	{
		while (in->str_input[c] && !ft_is_quote(in->str_input[c]) && flag == -1)
			c++;
		if (in->str_input[c] != '\0')
		{
			q = in->str_input[c];
			flag *= -1;
			c++;
		}
		while (in->str_input[c] && in->str_input[c] != q && flag == 1)
		{
			if (in->str_input[c] == ' ')
				in->str_input[c] = '\1';
			if (in->str_input[c] == q)
				flag *= -1;
			c++;
		}
	}
}

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

void ft_recovery_sp(t_input *input)
{
	int i;
	int c;

	i = -1;
	while (input->sp_input[++i])
	{
		c = -1;
		while (input->sp_input[i][++c])
		{
			if (input->sp_input[i][c] == '\1')
				input->sp_input[i][c] = ' ';
		}
	}
}