/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:44:06 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/02/09 10:06:59 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*funcion que sustituira el $NAME por el valor del entorno en el elemento
MIRAR BIEN PORQUE DEVUELVE UN NUM EN LUGAR DE UN VALOR PTE DE TENER EN CUENTA
$HOME$USER deberia de imprimir 2 variables de entorno en mi caso no encontraria
ninguna porque lo toma como una sola palabra el enfoque de como expandir hay 
que cambiarlo, se me ocurre si encuentra el dolar haz esto y continue en lugar
de hacerlo en una fncion aparte como esta ahora mismo*/
void	ft_expand_dollar(t_element *elm, t_data *d)
{
	int		c;

	c = -1;
	while (elm->data[++c])
	{
		if (elm->data[c] == '$')
		{
			ft_expand_init(elm, d, c);
			if (d->val)
			{
				d->aux = ft_insert_value(*elm, d->val, c, ft_strlen(d->var));
				elm->data = ft_strdup(d->aux);
				free (d->aux);
			}
			else if (!d->val && (!ft_val_id(d->var, 1) || !ft_isvar(d->var)))
				elm->type = 'z';
			else
				ft_expand_more(elm, d, c);
			free(d->var);
			free(d->val);
		}
	}
}

void	ft_expand_init(t_element *element, t_data *d, int c)
{
	d->var = NULL;
	d->val = NULL;
	d->var = ft_get_dollar_word(element->data, c + 1);
	d->val = ft_search_value(d->var, d->env_arr, d->env_size);
}

/**
 * TODO: recotar lineas ft_expand_dollar
 * 	- Las tres cadenas declaradas, a t_data, con nombres más cortos
 * 	- Cambiar y reducir nombre de ft_valid_identifier 
 * 	- (Si hace falta más recorte) función que libere dos cadenas (var + value)
 */

char	*ft_get_dollar_word(char *str, int start)
{
	char	*aux;
	int		c;

	c = start;
	while (str[c] && str[c] != '$' && !ft_is_space(str[c]) \
			&& !ft_is_quote(str[c]))
		c++;
	aux = ft_substr(str, start, c - start);
	return (aux);
}

/*en esta funcion vamos a buscar en el array de entorno
una coincidencia con la str *comp para obtener el valor
de la variab*/
char	*ft_search_value(char *comp, t_env *env, int lenv)
{
	int		i;
	char	*aux;

	i = -1;
	while (++i < lenv)
	{
		if (!ft_strcmp(comp, env[i].title))
		{
			aux = ft_strdup(env[i].line);
			return (aux);
		}
	}
	return (NULL);
}

char	*ft_insert_value(t_element elemento, char *value, int start, int del)
{
	char	*aux;
	int		c;
	int		i;
	int		j;

	c = -1;
	aux = malloc(sizeof(char) * ft_strlen(elemento.data) \
		+ ft_strlen(value) - del + 1);
	while (elemento.data[++c] && c < start)
		aux[c] = elemento.data[c];
	i = 0;
	j = c;
	while (value[i])
		aux[j++] = value[i++];
	c += del + 1;
	while (elemento.data[c])
	{
		aux[j++] = elemento.data[c++];
	}
	aux[j] = '\0';
	free(elemento.data);
	return (aux);
}

// char	*ft_clear_dollar(char *str, int pos)
// {
// 	char *aux;
// 	int	c;

// 	c = 0;
// 	aux = malloc(sizeof(char) * ft_strlen(str));//vamos a poner el numero de char a restar
// 	while (str[c])
// 	{
// 		while (str[c] && c < pos)
// 		{
// 			aux[c] = str[c];	
// 			c++;
// 		}
// 		if (str[c] == '$' && (str[c + 1] == '$' || ft_isdigit(str[c + 1])))
// 			c += 2;
// 		while (str[c] && (str[c + 1] != '$' || !ft_isdigit(str[c + 1])))
// 			aux[pos++] = str[c++];
// 	}
// 	aux[pos] = '\0';
// 	free(str);
// 	return (aux);
// }

//int ft_to_del_dollar(char *str)
