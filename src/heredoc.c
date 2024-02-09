/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:29:12 by pgruz11           #+#    #+#             */
/*   Updated: 2024/02/09 18:04:58 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_gsign_exit()

void	ft_is_heredoc(t_command *cmd, t_data *d)
{
	int		i;
	pid_t	pid;
	int		exit_stat;

	if (access(".heredoc", F_OK) == 0)
	{
		unlink(".heredoc");
		g_sign = 0;
	}
	i = -1;
	while (++i < cmd->size)
	{
		if (cmd->tokens[i].type == 'h')
		{
			signal(SIGINT, SIG_IGN);
			pid = fork();
			if (pid > 0)
			{
				waitpid(pid, &exit_stat, 0);
				if (WIFEXITED(exit_stat))
					d->exit_code = WEXITSTATUS(exit_stat);
				if (d->exit_code != 0)
					d->exit_code = g_sign;
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

int	ft_hdoc_ctrld(char *read, char *content)
{
	if (read == NULL && content == NULL)
	{
		rl_replace_line("> ", 0);
		exit(1);
	}
	if (read == NULL && content != NULL)
	{
		g_sign = 0;
		rl_replace_line("> ", 0);
		return (1);
	}
	return (0);
}

void	ft_heredoc(t_command *cmd, int pos, t_data *d)
{
	char	*content;
	char	*read;
	char	*eof;

	content = NULL;
	read = NULL;
	eof = NULL;
	if (cmd->tokens[pos + 1].type == 'e' || cmd->tokens[pos + 1].type == 'E')
		eof = cmd->tokens[pos + 1].data;
	read = readline("> ");
	if (read == NULL)
		exit (42);
	//ctrld = ft_hdoc_ctrld(read, content);
	if (ft_strcmp(read, eof))
	{
		while (ft_strcmp(read, eof))
		{
			content = ft_strjoint(content, read);
			content = ft_strjoint(content, "\n");
			free(read);
			read = readline("> ");
			if (read == NULL && content != NULL)
				break ;
			//ctrld = ft_hdoc_ctrld(read, content);
		}
		content = ft_expand_hdoc(content, d);
		ft_write_doc(cmd, content);
		if (content != NULL)
			free(content);
	}
	free(read);
}
