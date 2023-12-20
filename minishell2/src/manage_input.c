/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:31 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/20 15:01:25 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_manage_input(char *str_in, t_input *in)
{
	in->str_input = ft_strdup(str_in);
	ft_check_special_chars(in, in->str_input);
	ft_separate_quotes(in);
	in->sp_input = ft_split(in->str_input, ' ');
	ft_print_dstr(in->sp_input);
	ft_recovery_sp(in);
	ft_print_dstr(in->sp_input);
	in->n_elements = ft_strdlen(in->sp_input);
	ft_fill_elements(in);
}

/*Esta funcion chequea si hay un caracter especial(|,<,>, ;) pegado a un 
caracter imprimible si es asi añade un espacio con **ft_insert_space** 
para aislar el caracter especial antes de splitear 
ej: hola |amigo -> hola amigo solo lo hace por delante asi que 
requeriria otra funcion que lo haga con caracteres prespecial
PARECE QUE FUNCIONA BIEN PERO HAY QUE CHEQUEAR QUE NO ESTE ENTRE COMILLAS
EJ HOLA "AMIGO |MIO" LE PONDRIA EL ESPACIO
REVISAR FUNCION FT_IS_INQUOTE*/
void	ft_check_special_chars(t_input *in, char *str)
{
	int		c;
	char	*aux;
	char	q;

	c = -1;
	q = '0';
	aux = NULL;
	while (str[++c])
	{
		if (ft_is_special_char(str[c]) && ft_isprint(str[c + 1]) \
			&& str[c + 1] != '<' && str[c + 1] != '>')
		{
			//if !ft_in_quotes -> añade el espacio a la string;
			aux = ft_insert_space(str, c);
			printf("special identificados aux = %s\n", aux);
		}
	}
	if (aux)
		str = aux;
	in->str_input = str;
	printf("special no identificados str= %s\n", str);
}

/*funcion que sustituye la str pasada por arg con un espacio añadido a
continuacion de la pos pasada por arg se usa en ft_check_special_char */
char	*ft_insert_space(char *s, int pos)
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
	printf("aux 1 parte %s\n", aux);
	while (s[c])
	{
		aux[i++] = s[c++];
		printf(RED"llenando la 2 parte de aux %s\n aux[%c], s[%c]"RESET, aux, aux[i], s[c]);
	}	
	aux[i] = '\0';
	free(s);
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

/*FUNCION A REVISAR chequea si un caracter se encuentra entre comillas*/
int	ft_check_is_inquote(char *str, int c)
{
	int		i;
	int		j;
	int		flag;
	char	q;

	i = -1;
	j = ft_strlen(str);
	flag = -1;
	q = '0';
	while (str[++i])
	{
		if (ft_is_quote(str[i]) && flag == -1)
		{
			printf("comillas encontradas 1\n");
			q = str[i];
			flag *= -1;
			j = i;
		}
		if (ft_is_quote(str[i]) && str[i] == q)
		{
			printf("comillas encontrasa casadas\n");
			flag *= -1;
			if (c < j && c > i)
			{
				printf(YELLOW"el caracter esta entre comillas"RESET);
				return (0);
			}
		}
	}
	return (1);
}

/* ************************************************************************** */