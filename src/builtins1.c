/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:47:25 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/11/27 11:28:14 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(t_input *input)
{
	char buf[PATH_MAX];
	
	
	input->pwd = getcwd(buf, sizeof(buf));
	printf("%s\n", input->pwd);
	//free(buf);
}
