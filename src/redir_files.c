/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 09:35:55 by pgruz11           #+#    #+#             */
/*   Updated: 2023/12/26 10:48:51 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_open_check(int fd, char *file_path)
{
	if (fd == -1)
	{
		ft_printf("carcaribash: %s: %s\n", strerror(errno), file_path);
		exit(EXIT_FAILURE);
	}
}

void	ft_file_fds(t_command *cmd)
{
	int		i;

	i = -1;
	while (++i < cmd->size)
	{
		if (cmd->tokens[i].type == 'i')
		{
			if (cmd->fd_in != -1)
				close(cmd->fd_in);
			cmd->fd_in = open(cmd->tokens[i].data, O_RDONLY);
			ft_open_check(cmd->fd_in, cmd->tokens[i].data);
		}
		else if (cmd->tokens[i].type == 'o')
		{
			if (cmd->fd_out != -1)
				close(cmd->fd_out);
			cmd->fd_out = open(cmd->tokens[i].data,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			ft_open_check(cmd->fd_out, cmd->tokens[i].data);
		}
	}
}

void	ft_std_redir(t_command *cmd)
{
	ft_file_fds(cmd);
	if (cmd->fd_in != -1)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out != -1)
		dup2(cmd->fd_out, 1);
}
