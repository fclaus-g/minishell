/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:17:25 by pgruz11           #+#    #+#             */
/*   Updated: 2024/02/10 23:33:01 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*ft_var_del(char *s)
{
	char	*aux;
	int		i;
	int		len;

	i = 0;
	while (s[i] != '$')
		i++;
	len = 1;
	while (s[++i] != '\0' && s[i] != ' ' && s[i] != '\n' && s[i] != '$')
		len++;
	aux = malloc(sizeof(char) * ft_strlen(s) - len + 1);
	i = -1;
	len = -1;
	while (s[++i] != '$')
		aux[++len] = s[i];
	i++;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\n' && s[i] != '$')
		i++;
	while (s[i] != '\0')
		aux[++len] = s[i++];
	aux[++len] = '\0';
	free (s);
	return (aux);
}
