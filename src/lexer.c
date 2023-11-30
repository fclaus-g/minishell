/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:39:07 by pgruz11           #+#    #+#             */
/*   Updated: 2023/11/29 22:44:06 by pgomez-r         ###   ########.fr       */
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

/*Misma función que tengo de momento en init para que funcione el ejecutor
básico de momento, aquí voy a intentar ir reformulando para los primeros pasos
de lex-toke-parse
void	ft_fill_input(t_input *in, char *st)
{
	int	i;

	ft_tokenizer_qt(in, st);
	// in->sp_input = ft_split(st, ' ');
	// in->cmd_tab = ft_split(st, '|');
	// i = -1;
	// while (in->cmd_tab[++i] != NULL)
	// 	in->cmd_tab[i] = ft_strtrim_free(in->cmd_tab[i], " ");
	// in->cmd_n = ft_strdlen(in->cmd_tab);
	// in->n_elements = (int)ft_strdlen(in->sp_input);
	// i = -1;
	// while (in->sp_input[++i] != NULL)
	// 	in->elements[i].data = ft_strdup(in->sp_input[i]);
}
*/

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
	if ((c == '"' || c == '\'') && in_qt == -1)
		in_qt *= -1;
	else if ((c == '"' || c == '\'') && in_qt == 1)
	{
		in_qt *= -1;
	}
	return(in_qt);
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
	in_qt = -1;
	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_check_spc(str[i]))
		{
			while (ft_check_spc(str[i + 1]))
				i++;
			if (in_qt == -1 && str[i] != '\0')
				cnt++;
		}
		if (str[i] == '"' || str[i] == '\'')
			in_qt *= -1;
		// if ((str[i] == '"' || str[i] == '\'') && in_qt == -1)
		// 	in_qt *= -1;
		// else if ((str[i] == '"' || str[i] == '\'') && in_qt == 1)
		// {
		// 	in_qt *= -1;
		// }
	}
	return (cnt);
}

/*versión de split que deja la str de origen dividida por espacios pero
teniendo en cuenta las comillas*/
char	**ft_split_qt(char *str, int n)
{
	int				i;
	int				j;
	int				k;
	int				in_qt;
	char			**tab;

	i = 0;
	k = 0;
	tab = (char **)malloc(sizeof(char *) * (n + 1));
	if (!tab || !str)
		return (NULL);
	i = -1;
	k = 0;
	in_qt = -1;
	while (str[++i] != '\0')
	{
		while (ft_check_spc(str[i]))
			i++;
		in_qt = ft_quote_eval(str[i], in_qt);
		j = i;
		while (!ft_check_spc(str[i]) && str[i] != '"' && str[i] != '\'')
			i++;
		in_qt = ft_quote_eval(str[i], in_qt);
		if (i > j && in_qt == -1)
		{
			tab[k] = ft_savewords(str + j, i - j);
			k++;
		}
	}
	tab[k] = NULL;
	return (tab);
}

/*Recibe el struct del input (puede que haga falta el struct general?) y
convierte por primera vez el array de elementos separando y etiquetando
los que son entre comillas*/
void	ft_tokenizer_qt(t_input *in, char *s)
{
	int	i;
	int	n_elements;

	n_elements = (int)ft_wordcnt_qt(s);
	in->sp_input = ft_split_qt(s, n_elements);
	in->elements = malloc(sizeof(t_element) * n_elements);
	i = -1;
	while (++i < n_elements)
		in->elements[i].data = ft_strdup((const char *)in->sp_input[i]);
}

int	main(void)
{
	t_input	input;
	char	*input_line;
	int		i;
	int		j;

	input_line = "\"grep\" git\n";
	//input_line = "ls -la\n";
	i = (int)ft_wordcnt_qt(input_line);
	printf("En esta prueba, el num de elementos es 2\n");
	printf("El valor que devuelve wordcnt es: %d\n", i);
	ft_tokenizer_qt(&input, input_line);
	j = -1;
	while (++j < i)
		printf("Texto de elemento %d: %s\n", j, input.elements[j].data);
	return (0);
}
