/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_tools_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:59:50 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/05 23:17:16 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Para catalogar los nuevos elementos resultantes de la división del 
original, solo sirve dentro de ft_arr_update (de momento)*/
void	ft_tag_type(t_element *arr, int start, int size, char c)
{
	while (start < size)
	{
		if (ft_strchr(arr[start].data, c))
			arr[start].type = c;
		else
			arr[start].type = '0';
		start++;
	}
}

/*Para guardar el elemento separador de ft_element_split en su
propia cadena, que devolvemos para insertar en la posición de la
matriz de cadenas correspondiente*/
char	*ft_token_char(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

/*Versión equivalente al count_words de nuestro ft_split estandar
pero teniendo en cuenta que el elemento separador tiene su propia
cadena*/
size_t	ft_count_elements(char *str, char c)
{
	int		i;
	size_t	cnt;

	i = -1;
	cnt = 1;
	while (str[++i] != '\0')
	{
		while (str[i] != c && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			cnt++;
		if (str[i + 1] != '\0')
			cnt++;
	}
	return (cnt);
}
