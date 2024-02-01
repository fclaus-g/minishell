/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exegguttor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:21:34 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/31 18:55:56 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_built_exe(t_command *cmd, t_data *d)
{
	if (ft_std_redir(cmd) > 0)
		return ;
	if (ft_strcmp(cmd->cmd_tab[0], "echo") == 0)
		bi_echo(cmd->cmd_tab);
	else if (ft_strcmp(cmd->cmd_tab[0], "cd") == 0)
		bi_cd(d, cmd);
	else if (ft_strcmp(cmd->cmd_tab[0], "pwd") == 0)
		bi_pwd(d);
	else if (ft_strcmp(cmd->cmd_tab[0], "export") == 0)
		bi_export(d, cmd);
	else if (ft_strcmp(cmd->cmd_tab[0], "unset") == 0)
		bi_unset(d, cmd);
	else if (ft_strcmp(cmd->cmd_tab[0], "env") == 0)
		ft_print_dstr(d->env_dup);
	else if (ft_strcmp(cmd->cmd_tab[0], "exit") == 0)
		bi_exit(d);
}

void	ft_exegguttor(t_command *cmd, char **env)
{
	char	*str;
	pid_t	pid;

	if (ft_std_redir(cmd) > 0)
		return ;
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

void	ft_shell_pipex(t_data *d, int i)
{
	if (i != 0)
	{
		dup2(d->in.pipes[i - 1][0], 0);
		close(d->in.pipes[i - 1][0]);
	}
	if (i != d->in.cmd_n - 1)
	{
		dup2(d->in.pipes[i][1], 1);
		close(d->in.pipes[i][1]);
	}
}

int	ft_cmd_driver(t_data *d, t_command *cmds)
{
	int			curr_cmd;

	curr_cmd = -1;
	while (++curr_cmd < d->in.cmd_n)
	{
		ft_dollar_check(&cmds[curr_cmd], d);
		ft_std_shield(d, 0);
		ft_is_heredoc(&cmds[curr_cmd]);
		ft_shell_pipex(d, curr_cmd);
		if (cmds[curr_cmd].built == 1)
			ft_built_exe(&cmds[curr_cmd], d);
		else
			ft_exegguttor(&cmds[curr_cmd], d->env_dup);
		ft_std_shield(d, 1);
	}
	return (0);
}
