/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_temp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:08:47 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/12 19:19:30 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_repipex(t_data *d, int i)
{
	if (i != 0)
	{
		dup2(d->in.pipes[i - 1][0], 0);
		close(d->in.pipes[i - 1][0]);
		close(d->in.pipes[i - 1][1]);
	}
	if (i != d->in.cmd_n - 1)
	{
		dup2(d->in.pipes[i][1], 1);
		close(d->in.pipes[i][0]);
		close(d->in.pipes[i][1]);
	}
}

void	ft_init_pipes(t_input *in)
{
	int	i;

	in->pipes = malloc(sizeof(*in->pipes) * (in->cmd_n - 1));
	if (!in->pipes)
	{
		ft_printf_error("cascaribash: malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < in->cmd_n - 1)
	{
		if (pipe(in->pipes[i]) == -1)
		{
			ft_printf_error("cascaribash: pipe error\n");
			exit(EXIT_FAILURE);
		}
	}
}

int	ft_is_built(char *str)
{
	char	*builts[8];
	int		i;

	builts[0] = "echo\0";
	builts[1] = "cd\0";
	builts[2] = "pwd\0";
	builts[3] = "export\0";
	builts[4] = "unset\0";
	builts[5] = "env\0";
	builts[6] = "exit\0";
	builts[7] = NULL;
	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(str, builts[i]) == 0)
			return (1);
	}
	return (0);
}

void	ft_tag_builts(t_command *cmds, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (ft_is_built(cmds[i].cmd_tab[0]))
			cmds[i].built = 1;
	}
}

void	ft_bi_pipex(t_data *d, int curr_cmd)
{
	if (curr_cmd > 0)
	{
		close(d->in.pipes[curr_cmd - 1][1]);
		dup2(d->in.pipes[curr_cmd - 1][0], 0);
		close(d->in.pipes[curr_cmd - 1][0]);
	}
	if (curr_cmd < d->in.cmd_n - 1)
	{
		close(d->in.pipes[curr_cmd][0]);
		dup2(d->in.pipes[curr_cmd][1], 1);
		close(d->in.pipes[curr_cmd][1]);
	}
}

void	ft_std_shield(t_data *d, int mode)
{
	if (mode == 0)
	{
		d->og_stdin = dup(0);
		d->og_stdout = dup(1);
	}
	else
	{
		dup2(d->og_stdin, 0);
		dup2(d->og_stdout, 1);
		close(d->og_stdin);
		close(d->og_stdout);
	}
}

void	ft_built_exe(t_command *cmd, t_data *d)
{
	if (ft_strcmp(cmd->cmd_tab[0], "echo") == 0)
		bi_echo(cmd->cmd_tab);
	else if (ft_strcmp(cmd->cmd_tab[0], "cd") == 0)
		ft_printf("[%s] built not implemented yet.\n", cmd->cmd_tab[0]);
	else if (ft_strcmp(cmd->cmd_tab[0], "pwd") == 0)
		bi_pwd(d);
	else if (ft_strcmp(cmd->cmd_tab[0], "export") == 0)
		bi_export(d);
	else if (ft_strcmp(cmd->cmd_tab[0], "unset") == 0)
		ft_printf("[%s] built not implemented yet.\n", cmd->cmd_tab[0]);
	else if (ft_strcmp(cmd->cmd_tab[0], "env") == 0)
		bi_env(d);
	else if (ft_strcmp(cmd->cmd_tab[0], "exit") == 0)
		bi_exit(d);
}

void	ft_built_driver(t_command *cmd, t_data *d, int curr_cmd)
{
	(void)curr_cmd;
	ft_std_shield(d, 0);
	//ft_is_heredoc(cmd);
	//ft_bi_pipex(d, curr_cmd);
	ft_std_redir(cmd);
	ft_built_exe(cmd, d);
	ft_std_shield(d, 1);
}
