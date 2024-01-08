/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/08 10:41:31 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_manage_input(char *str_in, t_input *in)
{
	in->str_input = ft_strdup(str_in);
	//printf(BLUE"STR RECIBIDA POR INPUT-----> %s\n"RESET, in->str_input);
	ft_check_special_chars_right(in, in->str_input);
	ft_check_special_chars_left(in, in->str_input);
	//printf(GREEN"LA STR DE INPUT QUEDA ASI = %s\n"RESET, in->str_input);
	ft_separate_quotes(in);
	in->sp_input = ft_split(in->str_input, ' ');
	ft_recovery_sp(in);
	ft_print_dstr(in->sp_input);
	in->n_elements = ft_strdlen(in->sp_input);
	ft_fill_elements(in);
	ft_check_elements(in, in->element);
}

/*Esta funcion chequea si hay un caracter especial(|,<,>, ;) pegado a un 
caracter imprimible si es asi añade un espacio con **ft_insert_space** 
para aislar el caracter especial antes de splitear*/
void	ft_check_special_chars_right(t_input *in, char *str)
{
	int		c;
	char	*aux;

	c = -1;
	aux = NULL;
	while (str[++c])
	{
		if (ft_is_special_char(str[c]) && !ft_is_space(str[c + 1]) \
			&& str[c + 1] != '<' && str[c + 1] != '>')
		{
			if (!ft_in_quotes(str, c))
			{
				aux = ft_insert_right_space(str, c);
				if (aux)
					str = aux;
			}
		}
	}
	in->str_input = str;
	printf("str= %s str_input= %s\n", str, in->str_input);
}

/*funcion que sustituye la str pasada por arg con un espacio añadido a
continuacion de la pos pasada por arg se usa en ft_check_special_char */
char	*ft_insert_right_space(char *s, int pos)
{
	int		c;
	int		i;
	char	*aux;

	c = -1;
	aux = ft_calloc(sizeof(char), ft_strlen(s) + 2);
	while (++c <= pos)
		aux[c] = s[c];
	i = c;
	aux[i++] = ' ';
	while (s[c])
		aux[i++] = s[c++];
	aux[i] = '\0';
	return (aux);
}

/*Se llama antes de cada readline; en la primera ocasión inicia valores a 0
En el resto además libera las variables que han necesitado malloc en la lectura
anterior*/
void	ft_clean_input(t_input *input)
{
	int	i;

	i = -1;
	input->is_built = 0;
	input->is_redir = 0;
	input->n_pipe = 0;
	if (input->sp_input != NULL)
	{
		ft_totalfree(input->sp_input);
		while (++i < input->n_elements)
		{
			free(input->element[i].data);
		}
		free(input->element);
	}
	input->n_elements = 0;
}

void	ft_check_special_chars_left(t_input *in, char *str)
{
	int		c;
	char	*aux;

	c = 0;
	aux = NULL;
	while (str[c])
	{
		if (ft_is_special_char(str[c]) && !ft_is_space(str[c - 1]) \
			&& str[c - 1] != '<' && str[c - 1] != '>' && c >= 0)
		{
			if (!ft_in_quotes(str, c))
			{
				aux = ft_insert_left_space(str, c);
				if (aux)
					str = aux;
			}
		}
		c++;
	}
	in->str_input = str;
}

char	*ft_insert_left_space(char *s, int pos)
{
	int		c;
	int		i;
	char	*aux;

	c = -1;
	aux = ft_calloc(sizeof(char), ft_strlen(s) + 2);
	while (s[++c])
	{
		if (c < pos)
			aux[c] = s[c];
		else if (c == pos)
		{
			aux[c] = ' ';
			aux[c + 1] = s[c];
			i = c + 1;
		}
		else
			aux[++i] = s[c];
	}
	aux[++i] = '\0';
	return (aux);
}
/* ************************************************************************** */