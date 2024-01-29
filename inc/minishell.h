/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:04:00 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/29 14:23:59 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <sys/ioctl.h>
/*DEFS*/
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"
/*Types/Tokens*/
# define T_VOID '0' //sin tipo, sin catalogar todavía o literal
# define T_CMD 'c' //command (de momento no hace falta catalogar este tipo)
# define T_OPT 'o' //option (de momento no hace falta catalogar este tipo)
# define T_BLT 'b' //built (no se usa, tenemos built-in_flag en cada t_command)
# define T_PIP '|' //pipe
# define T_INF 'i' //infile - archivo entrada/input fd
# define T_OUF 'o' //outfile - archivo salida/output fd
# define T_APF 'O' //outfile para APPEND
# define T_DQT '\"' //bloque en comillas dobles
# define T_SQT '\'' //bloque comillas simples
# define T_VAR '$' //variable (si hay que expandir, si no tipo '0')
# define T_INR '<' //redirección entrada
# define T_OUR '>' //redirección salida
# define T_HDC 'h' //heredoc '<<'
# define T_APP 'a' //redirección salida con APPEND '>>'
# define T_EOF 'E' //end of file para heredoc (expande variables)
# define T_EOD 'e' //end of file para heredoc (no expande variables)

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
	int			fd_in;
	int			fd_out;
	int			fd_error;
	int			built;
	char		**paths;
	char		*path_cmd;
	char		*cmd_line;
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
	int			(*pipes)[2];
	char		**sp_input;
	// t_data		*data;
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
	char		**env_dup;
	char		**env_exp;
	t_env		*env_arr;
	int			env_size;
	char		*rl_input;
	int			og_stdin;
	int			og_stdout;
	t_input		in;
}	t_data;

extern int	listen;
/*main.c*/
void					ft_engine(t_data *d);
/*debug.c*/
void					ft_check_std(void);
void					debug_arr(t_input *in, char *str_in, char *msg);
void					debug_cmds(t_input *in, char *str_in, char *msg);
void					ft_print_element(t_element element);
/*init.c*/
void					ft_fill_input(t_input *in, char *st);
void					ft_split_env(t_data *d, char *var, size_t x);
void					ft_init(t_data *d, char **env);
void					ft_init_pipes(t_input *in);
/*signals.c*/
void 	ft_signal(void);
void	ft_handler(int sig);
void	ft_control_d(t_data *d);
/*manage_input.c*/
void					ft_manage_input(t_data *d);
/*manage_input_utils.c*/
int						ft_is_space(char c);
int						ft_is_special_char(char c);
/*quotes.c*/
void					ft_separate_quotes(t_data *d);
void					ft_recovery_sp(t_input *input);
int						ft_is_quote(char c);
int						ft_in_quotes(char *str, int c);
int						ft_quote_in_data(char *str);
/*quotes2.c*/
void					ft_management_quotes(t_element *element);
int						ft_closed_quotes(char *str);
char					ft_define_qtype(t_element element);
char					*ft_clean_quotes(t_element element);
int						ft_count_quotes(char *str);
/**********************[elements.c]***********************************/
void					ft_fill_elements(t_input *in);
void					ft_check_elements(t_input *in, t_element *array, t_data *d);
int						ft_its_dollar(char *str);
/**********************[expand.c]**************************************/
void					ft_expand_dollar(t_element *element, t_data *data);
char					*ft_get_dollar_word(char *str, int start);
char					*ft_search_value(char *comp, t_env *env, int lenv);
char					*ft_insert_value(t_element elemento, char *value, int start, int del);
/*lexer.c*/
int						ft_lexer(t_data *d);
void					ft_token_pipes(t_input *in);
void					ft_token_redirs(t_input *in);
int						ft_syntax_check(t_input *in);
void					ft_token_files(t_input *in);
/*lexer_utils.c*/
int						ft_is_red(char	*s);
void					ft_syntax_error(t_input *in, int i);
int						ft_eof_check(t_input *in);
/*cmd_maker.c*/
void					ft_cmd_maker(t_input *in);
void					ft_init_cmd(t_input *in);
void					ft_get_cmdline(t_input *in, t_command *cmds);
/*cmd_maker_utils.c*/
int						ft_element_cnt(t_input	*in, char c);
int						ft_cmd_size(t_input *in, int *start);
char					*ft_addspace(char *str);
void					ft_init_files(t_command *cmd);
/*redir_files.c*/
void					ft_file_fds(t_command *cmd);
void					ft_open_file(t_command *cmd, char *file, int type);
void					ft_open_check(t_command *cmd, int fd, char *file_path);
int						ft_std_redir(t_command *cmd);
void					ft_std_shield(t_data *d, int mode);
/*heredoc.c*/
void					ft_heredoc(t_command *cmd, int pos);
void					ft_write_doc(t_command *cmd, char *content);
void					ft_is_heredoc(t_command *cmd);
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
void					ft_built_exe(t_command *cmd, t_data *d);
void					ft_exegguttor(t_command *cmds, char **env);
void					ft_shell_pipex(t_data *d, int i);
int						ft_cmd_driver(t_data *d, t_command *cmds);
/*exegguttor_utils.c*/
int						is_path(char *str);
void					free_cache(t_command *st, int error);
void					split_cmd(t_command *st, char *cmdstr);
int						find_path_index(t_command *st, char *cmd);
void					get_paths(t_command *st, char **env);
/*bi_utils.c*/
void					ft_tag_builts(t_command *cmds, int len);
int						ft_is_built(char *str);
char					*ft_getenv(t_data *d, char *var);
/*bi_temp.c*/
void					bi_exit(t_data *d);
void					bi_echo(char **cmd_line);
/*bi_dir.c*/
void					bi_cd(t_data *d, t_command *cmd);
void					bi_pwd(t_data *d);
char					*ft_get_dir(char *arg);
char					*ft_dir_back(char *arg);
/*bi_exp.c*/
void					bi_export(t_data *d, t_command *cmd);
char					**ft_export_order(char **env);
void					ft_export_print(t_data *d);
int						ft_exp_argcheck(char *arg);
int						ft_export_chars(char c, int mode);
/*free.c*/
void					ft_clean_input(t_input *input);
void					ft_free_data(t_data *d);
void					ft_free_arr(t_input *in, int size);
void					ft_clean_exit(t_data *d);
void					ft_free_cmds(t_input *in);

#endif