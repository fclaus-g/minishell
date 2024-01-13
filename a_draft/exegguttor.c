/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exegguttor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:21:34 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/13 18:00:44 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exegguttor(t_command *cmd, char **env)
{
	char	*str;
	pid_t	pid;

	ft_std_redir(cmd);
	pid = fork();
	if (pid == -1)
		ft_printf_error("cascaribash: fork process failed");
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
	{
		str = NULL;
		get_paths(cmd, env);
		find_path_index(cmd, cmd->cmd_tab[0]);
		if (execve(cmd->path_cmd, cmd->cmd_tab, env) == -1)
		{
			str = cmd->cmd_tab[0];
			ft_printf_error("cascaribash: command not found: %s\n", str);
			free_cache(cmd, 127);
		}
	}
}

void	ft_repipex(t_data *d, int i)
{
	if (i != 0)
	{
		dup2(d->in.pipes[i - 1][0], 0);
		close(d->in.pipes[i - 1][0]);
		//close(d->in.pipes[i - 1][1]);
	}
	if (i != d->in.cmd_n - 1)
	{
		dup2(d->in.pipes[i][1], 1);
		//close(d->in.pipes[i][0]);
		close(d->in.pipes[i][1]);
	}
}

int	ft_cmd_driver(t_data *d, t_command *cmds)
{
	int			curr_cmd;

	curr_cmd = -1;
	while (++curr_cmd < d->in.cmd_n)
	{
		//ft_printf_error("[cmd %d] - Start\n", curr_cmd);
		ft_std_shield(d, 0);
		//ft_printf_error("[cmd %d] - Shield done - next heredoc\n", curr_cmd);
		ft_is_heredoc(&cmds[curr_cmd]);
		//ft_printf_error("[cmd %d] - heredoc done - next pipex\n", curr_cmd);
		ft_repipex(d, curr_cmd);
		//ft_printf_error("[cmd %d] - pipex done - next check\n", curr_cmd);
		if (ft_is_built(cmds[curr_cmd].cmd_tab[0]))
		{
			// ft_printf_error("[cmd %d] - is build - nex exe\n", curr_cmd);
			ft_built_driver(&cmds[curr_cmd], d);
			// ft_printf_error("[cmd %d] - built exe done - next shield back\n", curr_cmd);
		}
		else
			ft_exegguttor(&cmds[curr_cmd], d->env_dup);
		ft_std_shield(d, 1);
		// ft_printf_error("[cmd %d] - shield back done - next following cmd\n", curr_cmd);
	}
	return (0);
}

/**
 * TODO: redirecciones!-> comprobar si hay in/out file justo antes de
 *			cada llamada a exegguttor, y hacer dup con los fd si es así
 */