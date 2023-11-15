/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:04:00 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/15 12:35:17 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

/*STRUCTS*/
typedef struct s_input t_input;
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
	t_input	*in; //creo un puntero a la struct input para acceder a ella desde data
}	t_data;

/*Estructura para cada elemento del input, guarda tipo y su contenido en str*/
typedef struct s_element
{
	char	type;
	char	*data;
	int		fd_in;//para redirecciones se establece un valor standar y si hay redirecciones se cambia
	int		fd_out;//para redirecciones
	int		priority;//en algun momento creo que se debe decidir que ejecutar primero
}	t_element;

/*Estructura para la lectura del input completo, dentro guardamos varias flags
o info general y un array con todos los elementos de la linea, esto lo re-
utilizamos en cada lectura*/
typedef struct s_input
{
	int			n_elements; //número de elementos
	int			is_built; //hay built-in?
	int			is_redir; //hay redirecciones?
	int			n_pipe; //cuantos pipes?
	char		**sp_input; //splitted input en matriz de cadenas
	t_element	*elements; //array de structs - cada una un elemento
}	t_input;

/*main.c*/

/*init_structs.c*/
void					ft_init_structs(t_data *d, t_input *input);
void					ft_init_data(t_data *d);
void					ft_init_input(t_input *input);

/*init.c*/
void					ft_fill_input(t_input *in, char *st);
void					ft_split_env(t_data *d, char *var, size_t x);
void					ft_init(t_data *d, char **env, t_input *input);

/*checkin.c*/
void					ft_checkinput(t_input *input);
int						ft_is_builtin(char *str);
int						ft_is_redir(char *str);
int						ft_is_pipe(char *str);

/*exit.c*/
void					ft_clean_input(t_input *input);

#endif