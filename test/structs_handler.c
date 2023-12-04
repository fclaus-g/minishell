/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 21:39:30 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/04 19:40:57 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_token_char(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

size_t	ft_count_elements(char *str, char c)
{
	int		i;
	size_t	cnt;

	i = -1;
	cnt = 1;
	while (str[++i] != '\0')
	{
		while (str[i] != c && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			cnt++;
		if (str[i + 1] != '\0')
			cnt++;
	}
	return (cnt);
}

char	**ft_element_split(char *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	tab = malloc(sizeof(char *) * (ft_count_elements(str, c) + 1));
	i = 0;
	k = 0;
	//nueva teoria con update stack de gnl?
	while (str[i] != '\0')
	{
  		j = i;
        while (str[i] != c && str[i] != '\0')
            i++;
        if (i > j)
            tab[k++] = ft_savewords(str + j, i - j);
        if (str[i] == c)
        {
            tab[k++] = ft_token_char(c);
            i++;
        }
	}
	tab[k] = NULL;
	return (tab);
}

/*Llamar a la función cuando haga falta dividir y añadir elementos, con un if 
o funcion check antes en cada ft_token, si solo hay que catalogar el elemento
lo hacemos fuera, si hay que separar sus partes se hace aquí y se cataloga la
que estamos buscando, el resto queda indefinida*/
// t_element	*ft_list_update(t_input in, int i, char c)
// {
// 	char	**new_text;

// 	new_text = ft_element_split(in.elements[i].data, c);
// }

int	main(void)
{
	char	*str;
	char	**test;

	str = "hello|cabesa|wordl|||yestoque";
	test = ft_element_split(str, '|');
	ft_print_dstr(test);
	return (0);
}
