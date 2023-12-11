/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:40:28 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/11 21:22:48 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_tag_redtype(t_element *arr, int start, int size, char c)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strchr(arr[start].data, c))
		{
			if (c == '<')
				arr[start++].type = 'h';
			else if (c == '>')
				arr[start++].type = 'a';
		}
		else
			arr[start++].type = '0';
		i++;
	}
}

char	*ft_save_dbred(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 3);
	str[0] = c;
	str[1] = c;
	str[2] = '\0';
	return (str);
}

char	**ft_dbredir_split(char *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	tab = malloc(sizeof(char *) * ft_count_elements(str, c));
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		j = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (i > j)
			tab[k++] = ft_savewords(str + j, i - j);
		if (str[i] == c)
		{
			tab[k++] = ft_save_dbred(c);
			i += 2;
		}
	}
	tab[k] = NULL;
	return (tab);
}

t_element	*ft_db_redirs(t_input *in, int i, char c)
{
	char		**new_text;
	t_element	*new_arr;
	int			new_size;
	int			size;

	size = in->n_elements;
	new_text = ft_dbredir_split(in->elements[i].data, c);
	new_size = in->n_elements + (int)ft_strdlen(new_text) - 1;
	new_arr = malloc(sizeof(t_element) * new_size);
	in->n_elements = new_size;
	ft_fill_arr(in, new_arr, i, new_text);
	ft_tag_redtype(new_arr, i, (int)ft_strdlen(new_text), c);
	ft_totalfree(new_text);
	//ft_free_arr(in, size);
	free(in->elements);
	return (new_arr);
}

int	ft_is_red(char	*s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
			return (i);
	}
	return (-1);
}

void	ft_token_redirs(t_input *in)
{
	int	i;
	int	red;

	i = -1;
	while (++i < in->n_elements)
	{
		red = ft_is_red(in->elements[i].data);
		if (in->elements[i].type == '0' && red >= 0)
		{
			if (in->elements[i].data[red] == in->elements[i].data[red + 1]
				&& in->elements[i].data[red] != in->elements[i].data[red + 2])
				in->elements = ft_db_redirs(in, i, in->elements[i].data[red]);
			else if (ft_strlen(in->elements[i].data) > 1)
				in->elements = ft_arr_update(in, i, in->elements[i].data[red]);
			else
				in->elements[i].type = in->elements[i].data[red];
		}
	}
}

void	ft_token_pipes(t_input *in)
{
	int	i;

	i = -1;
	while (++i < in->n_elements)
	{
		if (in->elements[i].type == '0' && ft_strchr(in->elements[i].data, '|'))
		{
			if (ft_strlen(in->elements[i].data) > 1)
				in->elements = ft_arr_update(in, i, '|');
			else
				in->elements[i].type = '|';
		}
	}
}

void	ft_lexer(t_data *d, char *str_in)
{
	int		i;

	i = -1;
	ft_fill_input(&d->in, str_in);
	ft_token_pipes(&d->in);
	debug_arr(&d->in, str_in, "RESULTADO DESPUES DE TOKEN_PIPES");
	ft_token_redirs(&d->in);
}
