/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:12:51 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/15 17:48:06 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_red(char	*s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
			return (i);
	}
	return (-1);
}

void	ft_syntax_error(char c)
{
	char	*msg;

	msg = "cascaribash: syntax error near unexpected token ";
	if (c == '|')
		ft_printf_error("%s`|'\n", msg);
	if (c == '<')
		ft_printf_error("%s`<'\n", msg);
	if (c == '>')
		ft_printf_error("%s`>'\n", msg);
	if (c == 'h')
		ft_printf_error("%s`<<'\n", msg);
	if (c == 'a')
		ft_printf_error("%s`>>'\n", msg);
}
