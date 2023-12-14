/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:29:49 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/11 12:22:17 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

/*esta funcion  */
void	ft_separate_quotes(char *str)
{
	int c;
	int flag;
	char q;

	c = 0;
	flag = -1;
	while (str[c])
	{
		while (str[c] && !ft_is_quote(str[c]) && flag == -1)
			c++;	
		if (str[c] != '\0')
		{	
			q = str[c];
			flag *= -1;
			c++;
		}
		while (str[c++] && str[c] != q && flag == 1 )
		{
			if (str[c] == ' ')
				str[c] = '\1';
			if (str[c] == q)
				flag *= -1;
		}
	}
	printf("str: %s\n", str);
}
