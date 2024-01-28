/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:34:04 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/19 13:44:16 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*En ft_separate_quotes vamos a usar un caracter de control '\1' para 
cambiarlo por cada espacio que nos encontremos dentro de las comillas 
con la idea de hacer luego un split y las comillas se queden en una linea
de la matriz, a posteriori volveremos a cambiar el '\1' por ' '*/
void	ft_separate_quotes(t_data *d)
{
	int		c;
	int		flag;
	char	q;

	c = 0;
	flag = -1;
	while (d->rl_input[c])
	{
		while (d->rl_input[c] && !ft_is_quote(d->rl_input[c]) && flag == -1)
			c++;
		if (d->rl_input[c] != '\0')
		{
			q = d->rl_input[c];
			flag *= -1;
			c++;
		}
		while (d->rl_input[c] && d->rl_input[c] != q && flag == 1)
		{
			if (d->rl_input[c] == ' ')
				d->rl_input[c] = '\1';
			if (d->rl_input[c] == q)
				flag *= -1;
			c++;
		}
	}
}

/*funcion que recupera los caracteres de control '\1' por espacios de nuevo*/
void	ft_recovery_sp(t_input *input)
{
	int	i;
	int	c;

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

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

/*funcion que chequea si un caracter se encuentra entre comillas
solo chequea si el caracter esta detras de una comilla y la flag
no esta activa, NO COMPRUEBA SI LAS COMILLAS ESTAN CERRADAS*/
int	ft_in_quotes(char *str, int c)
{
	int		i;
	int		flag;

	i = -1;
	flag = -1;
	while (str[++i])
	{
		if (ft_is_quote(str[i]))
		{
			flag *= -1;
		}
		if (i == c && flag == 1)
		{
			return (1);
		}
	}
	return (0);
}

/*chequea si una string tiene comillas*/
int	ft_quote_in_data(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_is_quote(str[i]))
			return (1);
	}
	return (0);
}
