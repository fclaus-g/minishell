/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:11:58 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/01 07:30:43 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int ft_count_char(char *str, char c)
{
	int	i;
	int times;

	i = -1;
	times = 0;
	while (str[++i] && str[i])
	{
		if (str[i] == c)
			times++;
	}
	return (times);
}

void	diferenciar_comillas(int c, char *str)
{
	int quotes;
	int db_quotes;

	quotes = 0;
	db_quotes = 0;
	if (str[c] == '\'')
	{
		quotes = ft_count_char(&str[c], '\'');
		printf("quotes: %d\n", quotes);
	}
	else if (str[c] == '\"')
	{
		db_quotes = ft_count_char(&str[c], '\"');
		printf("db_quotes: %d\n", db_quotes);
	}	
}

void ft_lexer(char *str)
{
	int c;
	
	c = -1;
	
	while (str[++c] != '\0')
	{
		if (str[c] == '\'' || str[c] == '\"')
		{
			printf("qieto comillas, diferenciando... \n");
			diferenciar_comillas(c, str);
		}			
		c++;
	}
}
int main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_lexer(av[1]);
	}
	return (0);
}