/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comillas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:44:37 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/05 11:15:29 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int ft_count_quotes(char *str)
{
	int	i;
	int times;

	i = -1;
	times = 0;
	while (str[++i] && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			printf("str[%d]: %c\n", i, str[i]);
			times++;
		}
	}
	printf("times: %d\n", times);
	return (times);
}

void checkear_comillas(char *str)
{
	int c;
	int i;
	int quotes;
	char *aux;

	c = -1;
	i = 0;
	quotes = 0;
	printf("str: %s\n", str);
	while (str[++c])
	{
		if (str[c] == '\"' || str[c] == '\'')
		{
			quotes++;
			quotes += ft_count_quotes(&str[c]);
			i = c;
			while (str[c] != ' ' && c >= 0)
			{
				c--;
				printf("str[%d]: %c\n", c, str[c]);	
			}
			c++;
			break;
		}
	}
	while (str[++i] && quotes > 0)
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			printf("str[%d]: %c\n", i, str[i]);
			quotes--;
		}
	}
	aux = ft_substr(str, c, i);
	printf("aux: %s\n", aux);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		checkear_comillas(av[1]);
	}
}