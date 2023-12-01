/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:39:07 by pgruz11           #+#    #+#             */
/*   Updated: 2023/12/01 11:55:37 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	cnt;

	cnt = 0;
	while (cnt < n)
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	dest[cnt] = '\0';
	return (dest);
}

char	*ft_savewords(const char *s, unsigned int n)
{
	char			*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

/*TODO LO DE ARRIBA DE ESTO NO HACE FALTA ES POR NO VINCULAR CON MAKE + 
LIBERIA PARA COMPILAR SOLO ESTE ARCHIVO E IR HACIENDO PRUEBAS*/

/*ft para comprobar si un char coincide con algun separador, así acortamos
los while/if y ahorramos líneas*/
int	ft_check_spc(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

/*ft para evaluar el estado de la flag de comillas, la idea es mejorar la
función para tener en cuenta también si se trata de comilla que no cierra
que esta dentro de otras, impares, etc...no se me ocurre como de momento
Devuelve la flag actualizada*/
int	ft_quote_eval(char c, int in_qt)
{
	if (c == '"' || c == '\'')
		in_qt *= -1;
	return (in_qt);
}

/*ft para checkear si la str solo contiene espacios o separadores*/
int	ft_emptystr_check(char *str)
{
	int	i;

	if (str == NULL || *str == '\0')
		return (1);
	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_check_spc(str[i]))
			return (0);
	}
	return (1);
}

/**
 * @brief Función para contar los elementos teniendo en cuenta las comillas
 * Muy larga pero funciona, la comprobación de cadena vací o que solo contenga
	separadores se puede encapsular en una función a parte (líneas 24-34)
 * TODO: hacer que contemple bien el caso  "gr"ep" como un solo element!
 * TODO: estoy tratando " y ' igual, quizá hay que separarlo ("gre'p")
 */
size_t	ft_wordcnt_qt(char *str)
{
	int	i;
	int	cnt;
	int	in_qt;

	if (ft_emptystr_check(str))
		return (0);
	cnt = 0;
	i = -1;
	in_qt = -1;
	while (str[++i] != '\0')
	{
		while (ft_check_spc(str[i]) && str[i] != '\0')
			i++;
		cnt++;
		in_qt = ft_quote_eval(str[i], in_qt);
		if (in_qt == -1)
		{
			while (!ft_check_spc(str[i]) && str[i] != '\0')
				i++;
		}
		else
		{
			i++;
			while (in_qt == ft_quote_eval(str[i], in_qt) && str[i] != '\0')
				i++;
		}
	}
	return (cnt);
}

/*versión de split que deja la str de origen dividida por espacios pero
teniendo en cuenta las comillas*/

void	ft_split_qt(char *str, t_input *in)
{
	int				i;
	int				j;
	int				k;
	int				in_qt;

	i = 0;
	k = 0;
	in_qt = -1;
	while (str[i] != '\0')
	{
		while (ft_check_spc(str[i]) && str[i] != '\0')
			i++;
		j = i;
		in_qt = ft_quote_eval(str[i], in_qt);
		if (in_qt == -1)
		{
			while (!ft_check_spc(str[i]) && str[i] != '\0')
				i++;
			if (i > j)
			{
				in->elements[k].data = ft_savewords(str + j, i - j);
				k++;
			}
		}
		else
		{
			i++;
			while (in_qt == ft_quote_eval(str[i], in_qt) && str[i] != '\0')
				i++;
			i++;
			if (i > j)
			{
				in->elements[k].data = ft_savewords(str + j, i - j);
				k++;
			}
		}
	}
}

/*Recibe el struct del input (puede que haga falta el struct general?) y
convierte por primera vez el array de elementos separando y etiquetando
los que son entre comillas*/
int	ft_tokenizer_qt(t_input *in, char *s)
{
	//int	i;
	int	n_elements;

	n_elements = (int)ft_wordcnt_qt(s);
	if (n_elements == 0)
		return (printf("Input vacío\n"), 1);
	in->elements = malloc(sizeof(t_element) * n_elements);
	ft_split_qt(s, in);
	//i = -1;
	// while (++i < n_elements)
	// 	in->elements[i].data = ft_strdup((const char *)in->sp_input[i]);
	return (0);
}

int	main(void)
{
	t_input	input;
	char	*input_line;
	int		i;
	int		j;

	//input_line = "ls -la \"grep git\"";
	input_line = "\"grep \"git\" hola\"";
	i = (int)ft_wordcnt_qt(input_line);
	printf("INPUT PARA TEST: %s\n", input_line);
	printf("El valor que devuelve wordcnt (número de elementos) es: %d\n", i);
	if (ft_tokenizer_qt(&input, input_line) == 1)
		return (1);
	j = -1;
	while (++j < i)
		printf("Texto en input->elements[%d]: %s\n", j, input.elements[j].data);
	return (0);
}

/**
 * @brief Ahora mismo, la función separa elementos entre espacios y aisla en
 * un solo elemento lo que haya entre comillas, pero solo si viene todo ya
 * separado por espacios en el input
 * Por ejemplo: ls la"grep gi" no lo hace bien, en este caso lo primero que
 * falla es countword que saca muchos más elementos, creo que se puede ajustar
 * mejorando la ft para ver si hay que abrir o cerrar estado de comillas para
 * que evalue tambien que hay antes y despues del caracter de comilla
 * También, tanto en ft_count como en ft_splitqt, cuando estemos recorriendo
 * la str en el caso que tengamos quote en -1 (no estamos dentro de comillas)
 * deberían seguir chequeando si hay o no comilla, no solo espacio, lo puedo
 * replantear
 * TODO: check inputs con saltos de lineas dentro y al final
 */