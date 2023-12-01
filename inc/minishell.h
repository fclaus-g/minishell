 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:04:00 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/01 17:38:28 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

/*STRUCTS*/

/*Estructura que uso solamente para pipex/exegguttor de momento, veré si puedo
pasar sus elementos a otra de element o input o si es mejor tenerla aislada*/
typedef struct s_command
{
	char		**paths;
	char		*path_cmd;
	char		**cmd;
	t_element	*tokens;
}	t_command;

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
	int			cmd_n; //cuantos comandos?
	char		**sp_input; //splitted input en matriz de cadenas
	t_element	*elements; //array de structs - cada una un elemento
	t_command	*cmds;
}	t_input;

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
	t_input	in;
}	t_data;


/*main.c*/

/*init.c*/
void					ft_fill_input(t_input *in, char *st);
void					ft_split_env(t_data *d, char *var, size_t x);
void					ft_init(t_data *d, char **env);
char					*ft_strtrim_free(char *s1, char const *set);
/*checkin.c*/
int						ft_is_builtin(char **cmd_line);
int						ft_is_biexit(char *str);
/*exegguttor.c*/
int						ft_cmd_driver(t_input *in, char **env, t_data *d);
void					ft_pipex(char *cmd, char **env, int fd);
void					ft_exegguttor(char *cmd, char **env);
/*exegguttor_utils.c*/
int						is_path(char *str);
void					free_cache(t_command *st, int error);
void					split_cmd(t_command *st, char *cmdstr);
int						find_path_index(t_command *st, char *cmd);
void					get_paths(t_command *st, char **env);
/*builts_0.c*/
void					bi_exit(t_data *d, t_input *in);
void					bi_echo(char **cmd_line);
void					bi_export(t_data *d);
char					**ft_export_order(char **env);
void					bi_env(t_data *d);
void					ft_pwd(t_data *d);
/*lexer.c*/
void					ft_lexer(t_data *d, char *line);
/*lex_quotes.c*/
int						ft_check_spc(char c);
int						ft_quote_eval(char c, int in_qt);
int						ft_emptystr_check(char *str);
size_t					ft_wordcnt_qt(char *str);
void					ft_split_qt(char *str, t_input *in);
/*exit.c*/
void					ft_clean_input(t_input *input);
void					ft_free_data(t_data *d);

#endif