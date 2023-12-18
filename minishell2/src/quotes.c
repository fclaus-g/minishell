/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:34:04 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/18 14:55:14 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*En ft_separate_quotes vamos a usar un caracter de control '\1' para 
cambiarlo por cada espacio que nos encontremos dentro de las comillas 
con la idea de hacer luego un split y las comillas se queden en una linea
de la matriz, a posteriori volveremos a cambiar el '\1' por ' '*/
void	ft_separate_quotes(char *str)
{
	int		c;
	int		flag;
	char	q;

	c = 0;
	flag = -1;
	while (str[c])
	{
		while (str[c] && !ft_is_quote(str[c]) && flag == -1)
			c++;
		if (str[c] != '\0')
		{
			q = str[c];
			flag *= -1;
			c++;
		}
		while (str[c++] && str[c] != q && flag == 1 )
		{
			if (str[c] == ' ')
				str[c] = '\1';
			if (str[c] == q)
				flag *= -1;
		}
	}
	printf("str: %s\n", str);
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

/*en esta funcion vamos a recorrer la string con el input y si encontramos comillas retrocederemos 
hasta el espacio o hasta el caracter especial, h epensado que se podria insertar un espacio
para que quede en una string dentro de la matriz*/
void ft_prequotes(char *str, t_input *in)
{
	//int c;
	//char *aux;
	(void)str;
	(void)in;

}