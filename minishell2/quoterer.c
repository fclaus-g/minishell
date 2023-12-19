/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoterer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:53:24 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/19 13:42:01 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_count_tokens(char *str)
{
	int i;
	int tokens;
	int flag;
	char q;

	i = -1;
	tokens = 0;
	flag = -1;
	while (str[++i])
	{
		while (str[i] && !ft_is_quote(str[i]) && flag == -1)
		{
			
			if (str[i] = ' ')
			{	tokens++;
				while (str[i] == ' ')
				i++;
			}
			i++;
			if (str[i] = '"' && flag == -1)
			{
				q = str[i];
				flag *= -1;
				i++;
			}
			while (str[i] && str[i] != q && flag == 1)
			{
				if (str[i] == q)
					flag *= -1;
				i++;
				token++;
			}
		}	
		
	}
	return (tokens);
}


void ft_quoterer(char *str)
{
	int tokens;
	
	tokens = ft_count_tokens(str);
}

int main(void)
{
	char *str = "hi |aaaa\"hola que tal\" | como estas" ;

	ft_quoterer(str);
	return (0);
}