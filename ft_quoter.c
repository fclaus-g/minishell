/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:11:58 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/05 10:12:59 by fclaus-g         ###   ########.fr       */
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
		{
			printf("str[%d]: %c\n", i, str[i]);
			times++;
		}	
	}
	return (times);
}

void	diferenciar_comillas(int c, char *str)
{
	int quotes;
	int db_quotes;
	int last_quote;
	char *aux;

	aux = NULL;
	quotes = 0;
	db_quotes = 0;
	last_quote = 0;
	if (str[c] == '\'')
	{
		quotes = ft_count_char(&str[c], '\'');
		printf("quotes: %d\n", quotes);
	}
	else if (str[c] == '\"')
	{
		db_quotes = ft_count_char(str, '\"');
		printf("db_quotes: %d\n", db_quotes);
		while (db_quotes >= 0 && str[c] != '\0')
		{
			c++;
			if (str[c] == '\"')
			{
				printf("reducimos quote str[%d]: %c\n", c, str[c]);
				last_quote = c;
				db_quotes--;
			}
		}	
	}
	aux = ft_substr(str, 0, last_quote);
	printf("aux: %s\n", aux);	
}

void ft_quoter(char *str)
{
	int c;
	
	c = -1;
	
	while (str[++c] != '\0')
	{
		if (str[c] == '\'' || str[c] == '\"')
		{
			printf("qieto comillas, diferenciando... \n");
			diferenciar_comillas(c, str);
			break;
		}			
	}
}
int main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_quoter(av[1]);
	}
	return (0);
}