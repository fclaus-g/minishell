/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/09 10:07:54 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

void	ft_is_heredoc(t_command *cmd, t_data *d)
{
	int		i;
	pid_t	pid;
	int		exit_stat;

	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	i = -1;
	while (++i < cmd->size)
	{
		if (cmd->tokens[i].type == 'h')
		{
			pid = fork();
			if (pid > 0)
			{
				signal(SIGINT, SIG_IGN);
				waitpid(pid, &exit_stat, 0);
				if (WIFEXITED(exit_stat))
					d->exit_code = WEXITSTATUS(exit_stat);
				ft_signal();
			}
			else
			{
				signal(SIGINT, ft_here_sig);
				ft_heredoc(cmd, i, d);
				exit (0);
			}
		}
	}
}

void	ft_write_doc(t_command *cmd, char *content)
{
	int		fd;
	ssize_t	check;

	check = 0;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_open_check(cmd, fd, ".heredoc");
	if (content != NULL)
		check = write(fd, content, ft_strlen(content));
	if (check == -1)
	{
		cmd->dataptr->exit_code = 1;
		ft_printf("cascaribash: %s: %s\n", strerror(errno), ".heredoc");
	}
	close(fd);
}
/**
 * TODO: permisos para .heredoc al crearlo? 
 */

void	ft_heredoc(t_command *cmd, int pos, t_data *d)
{
	char	*content;
	char	*read;
	char	*eof;

	content = NULL;
	read = NULL;
	eof = NULL;
	signal(SIGINT, ft_here_sig);
	if (cmd->tokens[pos + 1].type == 'e' || cmd->tokens[pos + 1].type == 'E')
		eof = cmd->tokens[pos + 1].data;
	read = readline("> ");
	if (ft_strcmp(read, eof) && g_sign != 1)
	{
		while (ft_strcmp(read, eof) && g_sign != 1)
		{
			content = ft_strjoint(content, read);
			content = ft_strjoint(content, "\n");
			free(read);
			read = readline("> ");
		}
		content = ft_expand_hdoc(content, d);
		ft_write_doc(cmd, content);
		if (content != NULL)
			free(content);
	}
	free(read);
	ft_signal();
}
