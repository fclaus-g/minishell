/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/11 13:49:08 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_manage_input(char *str_in, t_input *in)
{
	in->str_input = ft_strdup(str_in);
	ft_check_special_chars_right(in, in->str_input);
	ft_check_special_chars_left(in, in->str_input);
	ft_separate_quotes(in);
	in->sp_input = ft_split(in->str_input, ' ');
	ft_recovery_sp(in);
	//ft_print_dstr(in->sp_input);
	in->n_elements = ft_strdlen(in->sp_input);
	ft_fill_elements(in);
	ft_check_elements(in, in->element);
	ft_print_array(in->element, in->n_elements);
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