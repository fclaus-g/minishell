/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:39:07 by pgruz11           #+#    #+#             */
/*   Updated: 2023/11/28 16:53:06 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	ft_count_elements_qts(char const *s)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && s[i] != ' ' && s[i] != 39 && s[i] != 34)
			i++;
	}
	return (count);
}

/*Qué hace cont_word = un ciclo con tres "checks" dentro:
while(recorrer toda la cadena original *s)
	while(si lo que hay en cada posicion de str == c, seguimos i++)
	if(terminado el while de arriba, porque str != c, aumentamos cntr+ 1 vez)
	while(si no ha terminado str y s[i] es distinto a c, seguimos i++)
Así ya tenemos el número de strings que va a tener nuestra tabla resultado*/

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