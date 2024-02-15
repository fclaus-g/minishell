/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:44:06 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/02/15 21:16:35 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_expand_excd(char *src, t_data *d)
{
	char	*code;
	char	*str;
	int		i;
	int		j;
	int		k;

	code = ft_itoa(d->exit_code);
	str = malloc(sizeof(char) * (ft_strlen(src) - 2 + ft_strlen(code) - 1));
	i = -1;
	j = -1;
	k = -1;
	while (src[++i] != '$')
		str[++j] = src[i];
	i++;
	while (code[++k] != '\0')
		str[++j] = code[k];
	while (src[++i] != '\0')
		str[++j] = src[i];
	str[++j] = '\0';
	free (code);
	return (str);
}

char	*ft_expand_other(char *content, t_data *d, int pos)
{
	char	*aux;

	aux = NULL;
	if (content[pos + 1] == '?')
	{
		aux = ft_expand_excd(content, d);
		free(content);
		return (aux);
	}
	return (content);
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

void	ft_quote_exp(char c, t_data *d)
{
	if (ft_is_quote(c) && d->q_flag == 0)
		ft_flag_check(d, c, 0);
	else if (c == d->q && d->q_flag == 1)
		ft_flag_check(d, c, 1);
}

char	*ft_expand(char *content, t_data *d)
{
	int		i;

	d->q = 0;
	d->q_flag = 0;
	i = -1;
	while (content[++i])
	{
		ft_quote_exp(content[i], d);
		if (content[i] == '$' && (d->q == 0 || d->q == '\"'))
		{
			ft_expand_init(content, d, i);
			if (d->val)
			{
				d->aux = ft_rplc_content(content, d->val, i, ft_strlen(d->var));
				content = ft_strdup(d->aux);
				free (d->aux);
			}
			else if (!d->val && (!ft_val_id(d->var, 1) || !ft_isvar(d->var)))
				content = ft_var_del(content, &i);
			else
				content = ft_expand_other(content, d, i);
			free(d->var);
			free(d->val);
		}
	}
	return (content);
}
