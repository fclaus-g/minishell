/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:20:43 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/11/29 10:29:33 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_input *input)
{
	int i;

	i = 0;
	while (input->data->env_dup[i])
	{
		printf("%s\n", input->data->env_dup[i]);
		i++;
	}
}