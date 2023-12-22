/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:04:00 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/22 03:00:17 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

/*DEFS*/
/*Types/Tokens*/
# define T_VOID 0
# define T_CMD 1
# define T_BLT 2
# define T_OPT 3
# define T_PIP 4
# define T_INF 5
# define T_OUF 6
# define T_DQT 7
# define T_SQT 8
# define T_VAR 9
# define T_INR 10
# define T_OUR 11
# define T_HDC 12
# define T_APP 13

/*STRUCTS*/
/*Estructura para cada elemento del input, guarda tipo y su contenido en str*/
typedef struct s_element
{
	char	type;
	char	*data;
}	t_element;

/*Estructura que uso solamente para pipex/exegguttor de momento, veré si puedo
pasar sus elementos a otra de element o input o si es mejor tenerla aislada*/
typedef struct s_command
{
	int			size;
	char		**paths;
	char		*path_cmd;
	char		**cmd_tab;
	t_element	*tokens;
}	t_command;

/*Estructura para la lectura del input completo, dentro guardamos varias flags
o info general y un array con todos los elementos de la linea, esto lo re-
utilizamos en cada lectura*/
typedef struct s_input
{
	int			n_elements;
	int			cmd_n;
	char		**sp_input;
	t_element	*elements;
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
void					debug_arr(t_input *in, char *str_in, char *msg);
void					debug_cmds(t_input *in, char *str_in, char *msg);
/*init.c*/
void					ft_fill_input(t_input *in, char *st);
void					ft_split_env(t_data *d, char *var, size_t x);
void					ft_init(t_data *d, char **env);
char					*ft_strtrim_free(char *s1, char const *set);
/*lexer.c*/
int						ft_lexer(t_data *d, char *str_in);
void					ft_token_pipes(t_input *in);
void					ft_token_redirs(t_input *in);
int						ft_syntax_check(t_input *in);
/*lexer_utils.c*/
int						ft_is_red(char	*s);
void					ft_syntax_error(char c);
/*cmd_maker.c*/
int						ft_element_cnt(t_input	*in, char c);
int						ft_cmd_size(t_input *in, int *start);
void					ft_cmd_assembler(t_input *in);
/*checkin.c*/
int						ft_is_builtin(char **cmd_line);
int						ft_is_biexit(char *str);
/*arr_tools_0.c*/
t_element				*ft_arr_update(t_input *in, int i, char c);
void					ft_fill_arr(t_input *in, t_element *new_arr, int tar, char **tab);
char					**ft_element_split(char *str, char c);
t_element				*ft_db_redirs(t_input *in, int i, char c);
char					**ft_dbredir_split(char *str, char c);
/*arr_tools_1.c*/
void					ft_tag_type(t_element *arr, int start, int size, char c);
char					*ft_write_token(char c);
size_t					ft_count_elements(char *str, char c);
void					ft_tag_redtype(t_element *arr, int start, int size, char c);
char					*ft_save_dbred(char c);
/*exegguttor.c*/
int						ft_cmd_driver(t_command *cmds, char **env, t_data *d);
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
/*builts_1.c*/
void					ft_pwd(t_data *d);
/*free.c*/
void					ft_clean_input(t_input *input);
void					ft_free_data(t_data *d);
void					ft_free_arr(t_input *in, int size);
void					ft_clean_exit(t_data *d, char *readline);

#endif