/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:17:25 by pgruz11           #+#    #+#             */
/*   Updated: 2024/02/04 23:11:01 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*******************************************************************/
/**********TODO ESTO A heredoc_expand.c************/
/*
- Modificar las ft para recibir cadena en lugar de element?
- Comprobar en ft_replace si tengo que pasarle puntero a puntero char**
*/
char	*ft_hd_exitcode(char *str, t_data *d, int pos)
{
	char	*code;
	char	*str;
	int		i;
	int		j;

	(void)pos;
	code = ft_itoa(d->exit_code);
	str = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(code) - 1));
	i = 1;
	j = -1;
	while (++j < (int)ft_strlen(code))
		str[j] = code[j];
	while (str[++i] != '\0')
		str[j++] = str[i];
	str[j] = '\0';
	free (code);
	return (str);
}

void	ft_exp_hdoc_misc(char *content, t_data *d, int pos)
{
	char	*aux;

	aux = NULL;
	if (content[pos + 1] == '?')
	{
		aux = ft_expand_exitcode(elm, d, pos);
		free(content);
		content = ft_strdup(aux);
		free(aux);
	}
	
}

char	*ft_rplc_content(char *content, char *value, int start, int del)
{
	char	*aux;
	int		c;
	int		i;
	int		j;

	c = -1;
	aux = malloc(sizeof(char) * ft_strlen(content) \
		+ ft_strlen(value) - del + 1);
	while (content[++c] && c < start)
		aux[c] = content[c];
	i = 0;
	j = c;
	while (value[i])
		aux[j++] = value[i++];
	c += del + 1;
	while (content[c])
	{
		aux[j++] = content[c++];
	}
	aux[j] = '\0';
	free (content);
	return (aux);
}

void	ft_exphd_init(char *content, t_data *d, int i)
{
	d->var = NULL;
	d->val = NULL;
	d->var = ft_get_dollar_word(content, i + 1);
	d->val = ft_search_value(d->var, d->env_arr, d->env_size);
}

char	*ft_expand_hdoc(char *content, t_data *d)
{
	int		i;
	char	*str;

	i = -1;
	while (content[++i])
	{
		if (content[i] == '$')
		{
			ft_exphd_init(content, d, i);
			if (d->val)
			{
				d->aux = ft_rplc_content(content, d->val, i, ft_strlen(d->var));
				content = ft_strdup(d->aux);
				free (d->aux);
			}
			else if (!d->val && (!ft_val_id(d->var, 1) || !ft_isvar(d->var)))
				elm->type = 'z'; //aqui dejar cadena vacia
			else
				ft_exp_hdoc_misc(content, d, i);
			free(d->var);
			free(d->val);
		}
	}
}

/*************************************************************/

void	ft_expand_more(t_element *elm, t_data *d, int pos)
{
	char	*aux;

	aux = NULL;
	if (elm->data[pos + 1] == '?')
	{
		aux = ft_expand_exitcode(elm, d, pos);
		free(elm->data);
		elm->data = ft_strdup(aux);
		free(aux);
	}
	
}

char	*ft_expand_exitcode(t_element *elm, t_data *d, int pos)
{
	char	*code;
	char	*str;
	int		i;
	int		j;

	(void)pos;
	code = ft_itoa(d->exit_code);
	str = malloc(sizeof(char) * (ft_strlen(elm->data) + ft_strlen(code) - 1));
	i = 1;
	j = -1;
	while (++j < (int)ft_strlen(code))
		str[j] = code[j];
	while (elm->data[++i] != '\0')
		str[j++] = elm->data[i];
	str[j] = '\0';
	free (code);
	return (str);
}
