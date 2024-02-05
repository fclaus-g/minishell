/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:29:12 by pgruz11           #+#    #+#             */
/*   Updated: 2024/02/05 12:09:41 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_is_heredoc(t_command *cmd, t_data *d)
{
	int	i;

	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	i = -1;
	while (++i < cmd->size)
	{
		if (cmd->tokens[i].type == 'h')
			ft_heredoc(cmd, i, d);
	}
}

void	ft_write_doc(t_command *cmd, char *content)
{
	int		fd;
	ssize_t	check;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_open_check(cmd, fd, ".heredoc");
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
	if (cmd->tokens[pos + 1].type == 'e' || cmd->tokens[pos + 1].type == 'E')
		eof = cmd->tokens[pos + 1].data;
	read = readline("> ");
	if (ft_strcmp(read, eof))
	{
		while (ft_strcmp(read, eof))
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
}
