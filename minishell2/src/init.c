/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:01:35 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/18 14:57:39 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*en este archivo vamos a inicias las structs para evitar basura dentro
 de las variables*/
void	ft_init(t_data *d, char **env, t_input *in)
{
	ft_init_data(d, in);
	ft_init_input(d, in);
	ft_init_env(d, env);
}

void	ft_init_data(t_data *d, t_input *in)
{
	d->env_dup = NULL;
	d->env_arr = NULL;
	d->in = in;
}

void	ft_init_input(t_data *d, t_input *in)
{
	in->n_elements = 0;
	in->is_built = 0;
	in->is_flag = 0;
	in->is_redir = 0;
	in->n_pipe = 0;
	in->n_lines = 0;
	in->n_words = 0;
	in->sp_input = NULL;
	in->element = NULL;
	in->data = d;
}

/*en ft_init_env vamos a llenar la estructura env(dentro de data)
que guarda el entorno de 2 maneras, en una matriz el entorno completo 
y en un array de struct, cada struct almacenará la linea completa, el titulo 
y el valor*/
void	ft_init_env(t_data *d, char **env)
{
	size_t	i;

	i = -1;
	d->env_dup = env;
	d->env_arr = malloc(sizeof(t_env) * ft_strdlen(d->env_dup));
	while (++i < ft_strdlen(d->env_dup))
	{
		d->env_arr[i].full = ft_strdup(env[i]);
		ft_split_env(d, env[i], i);
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
	d->env_arr[x].title = malloc(sizeof(char) * i + 1);
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
