/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:02:42 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/01/16 11:03:30 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_its_dollar(char *str)
{
	int	c;

	c = -1;
	while (str[++c])
	{
		if (str[c] == '$')
			return (1);
	}
	return (0);
}

void	ft_print_element(t_element element)
{
	printf(BLUE"element.data = %s\n"RESET, element.data);
	printf(YELLOW"element.type = %c\n"RESET, element.type);
	printf(YELLOW"element.fd_in = %d\n"RESET, element.fd_in);
	printf(YELLOW"element.fd_out = %d\n"RESET, element.fd_out);
	printf(YELLOW"element.priority = %d\n"RESET, element.priority);
	printf(YELLOW"element.pos = %d\n"RESET, element.pos);
}
