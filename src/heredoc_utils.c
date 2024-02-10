/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:02:55 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/10 23:16:41 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_content_buffer(t_data *d)
{
	d->content = ft_strjoint(d->content, d->read);
	d->content = ft_strjoint(d->content, "\n");
	free(d->read);
}

void	ft_heredoc_init(t_data *d, t_command *cmd, int pos)
{
	d->content = NULL;
	d->read = NULL;
	d->eof = NULL;
	if (cmd->tokens[pos + 1].type == 'e' || cmd->tokens[pos + 1].type == 'E')
		d->eof = cmd->tokens[pos + 1].data;
}
