/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:04:00 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/13 11:45:05 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

/*STRUCTS*/

typedef struct s_env
{
	char	*full;
	char	*title;
	char	*line;
}	t_env;

typedef struct s_data
{
	char	**env_dup;
	t_env	*env_arr;
}	t_data;
/*De momento no se me ocurre nada para la struct general, conforme vayamos
probando cosas nos daremos cuenta de qué necesitamos meter*/

typedef struct s_input
{
	char	*str_in;
	int		is_bltn;
	int		is_file;
	int		n_pips;
	char	type;
	char	*name;
}	t_input;

/*main.c*/

#endif