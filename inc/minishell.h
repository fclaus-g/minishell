/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:04:00 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/05 13:49:22 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

/*STRUCTS*/
typedef struct s_input t_input;
typedef struct s_element t_element;
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
	t_element	*next;
}	t_element;


/*Estructura para la lectura del input completo, dentro guardamos varias flags
o info general y un array con todos los elementos de la linea, esto lo re-
utilizamos en cada lectura*/
typedef struct s_input
{
	int			n_elements; //número de elementos
	int			is_built; //hay built-in?
	int			is_flag; //hay flags?
	int			is_redir; //hay redirecciones?
	int			n_pipe; //cuantos pipes?
	int			n_lines; //cuantas lineas?
	char		*pwd;
	char		**sp_input; //splitted input en matriz de cadenas
	char		**sp_pipe; //splitted input por pipes
	t_element	*elements; //array de structs - cada una un elemento
	t_data		*data; //puntero a la struct data
}	t_input;

/*main.c*/

/*init_structs.c*/
void					ft_init_structs(t_data *d, t_input *input);
void					ft_init_data(t_data *d, t_input *input);
void					ft_init_input(t_data *d, t_input *input);

/*init.c*/
void					ft_fill_input(t_input *in, char *st);
void					ft_split_env(t_data *d, char *var, size_t x);
void					ft_init(t_data *d, char **env, t_input *input);
void	ft_check_quotes_str(char *str, t_input *input);
int ft_count_char(char *str, char c);
/*checkin.c*/
void					ft_checkinput(t_input *input);
int						ft_is_builtin(char *str, t_input *input);
int						ft_is_redir(char *str);
int						ft_is_pipe(char *str);
void					ft_check_c(t_input *input);
void					ft_check_dollar(t_input *input);

/*pipe_chekin.c*/
void				ft_pipe_checkinput(t_input *input);
void				ft_print_matriz(char **matriz);
/*exit.c*/
void					ft_clean_input(t_input *input);

/*builtins.c*/
void					ft_pwd(t_input *input);
void					ft_echo(t_input *input);

/*ft_env.c*/
void					ft_env(t_input *input);
/*ft_export.c*/
void	ft_export(t_input *input);
char	**ft_export_order(char **env);
/*lexer.c*/
void	ft_lexer(char *str, t_input *input);
/*quotes.c*/
int ft_start_quotes(char *str);
int	ft_count_quotes(char *str);
int ft_end_quotes(char *str);

/*ft_split_ms.c*/
char	**ft_split_ms(char const *s, char c);

#endif