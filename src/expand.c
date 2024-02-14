/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/14 10:26:22 by fclaus-g         ###   ########.fr       */
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

char	*ft_expand(char *content, t_data *d)
{
	int		i;

	i = -1;
	while (content[++i])
	{
		if (content[i] == '$')
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
