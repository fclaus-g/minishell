/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 07:32:32 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/04 23:18:32 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Archivo para funciones que inicien nuestras structs, si nos pasamos de
funcionemos podemos ir sacando a archivos utils.c las auxiliares (como
ft_split_env por ejemplo)*/

#include "../inc/minishell.h"

char	*ft_strtrim_free(char *s1, char const *set)
{
	char	*aux;

	aux = ft_strtrim(s1, set);
	free(s1);
	return (aux);
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
		in->elements[i].type = NULL;
	}
}

/*A esta función le entra una variable de entorno completa en una str
Lo que hace es dividirla y guardar por un lado el nombre de la variable (antes
de '=') y por otro el contenido o ruta (después de '='), ambos se quedan
guardados por separado en la struct que tenemos para cada variable de entorno*/
void	ft_split_env(t_data *d, char *var, size_t x)
{
	int	i;
	int	j;

	i = 1;
	while (var[i] != '=')
		i++;
	d->env_arr[x].title = malloc(sizeof(char) * i);
	i = -1;
	while (var[++i] != '=')
		d->env_arr[x].title[i] = var[i];
	d->env_arr[x].title[i] = '\0';
	i++;
	j = i;
	while (var[i] != '\0')
		i++;
	d->env_arr[x].line = malloc(sizeof(char) * (i + 1) - j);
	i = j - 1;
	j = -1;
	while (var[++i] != '\0')
		d->env_arr[x].line[++j] = var[i];
	d->env_arr[x].line[j + 1] = '\0';
}

/*De momento solo copia las variables de entorno, más adelante podemos inciar
aquí también variables que vayamos añadiendo a la struct general*/
void	ft_init(t_data *d, char **env)
{
	size_t	i;

	d->env_dup = env;
	d->env_arr = malloc(sizeof(t_env) * ft_strdlen(d->env_dup));
	i = -1;
	while (++i < ft_strdlen(d->env_dup))
	{
		d->env_arr[i].full = ft_strdup(d->env_dup[i]);
		ft_split_env(d, env[i], i);
	}
}
