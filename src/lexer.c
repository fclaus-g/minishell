/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:04:06 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/01 18:45:52 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_input
{
	int			n_elements; //número de elementos
	int			cmd_n; //cuantos comandos?
	char		**sp_input; //splitted input en matriz de cadenas
	t_element	*elements; //array de structs - cada una un elemento
	t_command	*cmds; //array de comandos completos, que a su vez contiene array de elementos (pero solo los correspondientes a cada comando)
}	t_input;

typedef struct s_element
{
	char	type;
	char	*data;
}	t_element;

typedef struct s_command
{
	char		**paths; //estos tres primeros lo usa el último paso de executor solo si no es built in
	char		*path_cmd; //al generar el t_command en lexer, los ponemos NULL para evitar problemas
	char		**cmd; //luego si hace falta en executor le dará un valor para usarlos
	t_element	*tokens; //array de elementos igual que el que tenemos en input, pero incluimos los que sabemos que necesitamos para ejecutar
}	t_command;

void	ft_lexer(t_data *d, char *line)
{
	ft_split_qt(line, d->in); //se queda elementos guardados aislando en bloques las comillas
	//ft_token_qt(d->in); //se asigna el type a los elementos que sean entre comillas
	//ft_token_pipe(d->in); //se separan y etiquetan los elementos que sean pipe
	//ft_token_redir(d->in); //se separan y etiquetan las redir
	//ft_token_files(d->in); //según tipo de redir, separar y poner token de archivo a los elementos que estén antes/después
	//ft_command_assemble(d->in); //con todo separado y etiquetado, generar comandos completos para enviar a cmd_driver
}

/**
 * TODO: configurar función cada SEPARACIÓN por tipo (nuevo array + orden correcto + free)
 * 
 */