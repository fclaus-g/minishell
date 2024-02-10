/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:49:07 by pgruz11           #+#    #+#             */
/*   Updated: 2024/02/10 23:32:52 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_hd_exitcode(char *src, t_data *d)
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

char	*ft_exp_hdoc_misc(char *content, t_data *d, int pos)
{
	char	*aux;

	aux = NULL;
	if (content[pos + 1] == '?')
	{
		aux = ft_hd_exitcode(content, d);
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
				content = ft_var_del(content);
			else
				content = ft_exp_hdoc_misc(content, d, i);
			free(d->var);
			free(d->val);
			i = -1;
		}
	}
	return (content);
}

/*************************************************************/
