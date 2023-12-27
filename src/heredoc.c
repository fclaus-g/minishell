/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:29:12 by pgruz11           #+#    #+#             */
/*   Updated: 2023/12/27 23:45:49 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_heredoc(t_command *cmd, int pos)
{
	char	*content;
	char	*read;
	char	*eof;

	content = NULL;
	read = NULL;
	eof = NULL;
	if (cmd->tokens[pos + 1].type == 'e' || cmd->tokens[pos + 1].type == 'E')
		eof = cmd->tokens[pos + 1].data;
	while (read != eof || pos > -1)
	{
		read = readline("> ");
		content = ft_strjoint(content, read);
		free(read);
		pos = -1;
	}
	//open file con modos para temp, nombre heredoc y save content en el
}
