/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:44:06 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/08 14:35:06 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*funcion que sustituira el $NAME por el valor del entorno en el elemento
MIRAR BIEN PORQUE DEVUELVE UN NUM EN LUGAR DE UN VALOR
PTE DE TENER EN CUENTA $HOME$USER deberia de imprimir 2 variables de entorno
en mi caso no encontraria ninguna porque lo toma como una sola palabra
el enfoque de como expandir hay que cambiarlo, se me ocurre si encuentra el dolar
haz esto y continue en lugar de hacerlo en una fncion aparte como esta ahora mismo*/
void	ft_expand_dollar(t_element element, t_data *data)
{
	char	*aux;
	int		env_pos;
	
	aux = ft_get_dollar_word(element.data);
	env_pos = ft_search_value(aux, data->env_arr, data->env_size);
	printf("valor de env = %s", data->env_arr[env_pos].line);
}

char	*ft_get_dollar_word(char *str)
{
	char *aux;
	int c;
	int start;
	int	len;

	c = -1;
	while (str[++c])
	{
		if (str[c] == '$')
		{
			start = c;
			while (!ft_is_space(str[c]) && str[c] != '$' && str[c])
				c++;
			len = c;
		}
	}
	printf("c = %d\n", len);
	aux = ft_substr(str, start, c - start);
	printf ("aux = %s\n", aux);
	return (aux);
}

/*en esta funcion vamos a buscar en el array de entorno
una coincidencia con la str *comp para obtener el valor
de la variab*/
int ft_search_value(char *comp, t_env *env, int lenv)
{
	int	i;

	i = -1;
	while (++i < lenv)
	{
		if (ft_strcmp(comp, env[i].title))
			return(i);
	}
	return (0);
}
