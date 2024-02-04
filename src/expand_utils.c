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
