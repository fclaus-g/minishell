/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:17:25 by pgruz11           #+#    #+#             */
/*   Updated: 2024/02/16 18:23:44 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_expand_init(char *content, t_data *d, int i)
{
	d->var = NULL;
	d->val = NULL;
	d->var = ft_get_dollar_word(content, i + 1);
	d->val = ft_search_value(d->var, d->env_arr, d->env_size);
}

char	*ft_get_dollar_word(char *str, int start)
{
	char	*aux;
	int		c;

	c = start;
	while (str[c] && str[c] != '$' && !ft_is_space(str[c]) \
			&& !ft_is_quote(str[c]))
		c++;
	aux = ft_substr(str, start, c - start);
	return (aux);
}

/*en esta funcion vamos a buscar en el array de entorno
una coincidencia con la str *comp para obtener el valor
de la variab*/
char	*ft_search_value(char *comp, t_env *env, int lenv)
{
	int		i;
	char	*aux;

	i = -1;
	while (++i < lenv)
	{
		if (!ft_strcmp(comp, env[i].title))
		{
			aux = ft_strdup(env[i].line);
			return (aux);
		}
	}
	return (NULL);
}

char	*ft_var_del(char *s, int *pos)
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
	(*pos) = -1;
	return (aux);
}

void	ft_quotes(t_command *cmd, t_data *d)
{
	int	i;

	i = -1;
	while (++i < cmd->size)
		cmd->tokens[i].data = ft_clean_quotes(&cmd->tokens[i], d);
}
