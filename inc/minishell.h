/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:04:00 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/21 22:31:43 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

/*STRUCTS*/
/*Estructura para cada variable de entorno (tendremos que crear un array de
este tipo de struct)*/
typedef struct s_env
{
	char	*full;
	char	*title;
	char	*line;
}	t_env;

/*Estructura "general", iremos añadiendo elementos según vayamos necesitando*/
typedef struct s_data
{
	char	**env_dup;
	t_env	*env_arr;
}	t_data;

/*Estructura para cada elemento del input, guarda tipo y su contenido en str*/
typedef struct s_element
{
	char	type;
	char	*data;
}	t_element;

/*Estructura para la lectura del input completo, dentro guardamos varias flags
o info general y un array con todos los elementos de la linea, esto lo re-
utilizamos en cada lectura*/
typedef struct s_input
{
	int			n_elements; //número de elementos
	int			is_built; //hay built-in?
	int			is_redir; //hay redirecciones?
	int			cmd_n; //cuantos comandos?
	int			fd_in; //entero para guardar el fd despues de abrir infile si hay
	int			fd_out; //entero para guardar el fd después de abrir outfile si hay
	char		**sp_input; //splitted input en matriz de cadenas
	t_element	*elements; //array de structs - cada una un elemento
}	t_input;

/*Estructura que uso solamente para pipex/exegguttor de momento, veré si puedo
pasar sus elementos a otra de element o input o si es mejor tenerla aislada*/
typedef struct s_command
{
	char	**paths;
	char	*path_cmd;
	char	**cmd;
}	t_command;

/*main.c*/

/*init.c*/
void					ft_fill_input(t_input *in, char *st);
void					ft_split_env(t_data *d, char *var, size_t x);
void					ft_init(t_data *d, char **env);
/*exegguttor.c*/

/*exegguttor_utils.c*/

/*exit.c*/
void					ft_clean_input(t_input *input);

#endif