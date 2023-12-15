/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 07:32:32 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/07 21:21:18 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Archivo para funciones que inicien nuestras structs, si nos pasamos de
funcionemos podemos ir sacando a archivos utils.c las auxiliares (como
ft_split_env por ejemplo)*/

#include "../inc/minishell.h"

/*Función para guardar el input que está en formato str después de readline en 
el formato de doble matrix y array de estructuras que queremos para usarlo
En el mismo bucle podemos ir llamando a la función lexer cuando la tengamos*/
void	ft_fill_input(t_input *in, char *st)
{
	int	i;

	ft_lexer(st, in);
	in->sp_input = ft_split(st, ' ');
	in->sp_pipe = ft_split(st, '|');//vamos a guardar una matriz con el split como separador
	in->elements = malloc(sizeof(t_element) * ft_strdlen(in->sp_input));
	i = -1;
	// while (in->sp_pipe[++i] != NULL)
	// {
	// 	in->sp_pipe[i] = ft_strtrim(in->sp_pipe[i], " ");
	// }
	ft_print_matriz(in->sp_input);
	i = -1;
	while (in->sp_input[++i] != NULL)
	{
		in->elements[i].data = ft_strdup(in->sp_input[i]);
		in->elements[i].type = 0;
		in->elements[i].fd_in = 0;
		in->elements[i].fd_out = 1;//por defecto entrada y salida estandar
		in->elements[i].priority = 0;
	}	
	in->n_elements = i;
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
void	ft_init(t_data *d, char **env, t_input *input)
{
	size_t	i;

	ft_init_structs(d, input);//voi a iniciar las structs en una funcion aparte
	d->env_dup = env;
	d->env_arr = malloc(sizeof(t_env) * ft_strdlen(d->env_dup));
	d->in = input;
	i = -1;
	while (++i < ft_strdlen(d->env_dup))
	{
		d->env_arr[i].full = ft_strdup(d->env_dup[i]);
		ft_split_env(d, env[i], i);
	}
}

