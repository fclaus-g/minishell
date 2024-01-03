/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exegguttor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:21:34 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/03 21:07:47 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Función que ejecuta los comandos de la consola con execve, tal
 * como la tenía en pipex 
 * @param cmds = struct de comando = array de elementos del input
 * TODO: test get_paths en line.35 (para hacerlo solo si vamos por excve)
 * TODO: files_fd lo primero, si hay redirs, los fds se quedan cambiados
	y al estar en un proceso a parte, al terminar se cierran solos
 */

void	ft_exegguttor(t_command *cmd, char **env)
{
	char	*str;

	ft_std_redir(cmd);
	str = NULL;
	split_cmd(cmd, cmd->cmd_line);
	if (!ft_is_builtin(cmd->cmd_tab))
		exit(0);
	if (ft_is_biexit(cmd->cmd_tab[0]))
		exit(0);
	else
	{
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

/**
 * ft_pipex genera un pipe para que "comunique" el output del primer comando
 * al siguiente comando, que lo tomará como input
 * fork() genera procesos nuevos dentro del mismo programa
 * dup() intercambia file descriptors del sistema, nos permite hacer que el fd de
 * un archivo que hemos abierto pase a ser el fd 0 de standard input
 * el proceso generado ejecuta cada comando que entra por consola, usando excve()
 */
void	ft_pipex(t_command *cmd, char **env, int fd)
{
	pid_t	pid;
	int		pipe_end[2];

	pipe(pipe_end);
	pid = fork();
	if (pid == -1)
		perror("cascaribash: fork process failed");
	else if (pid > 0)
	{
		close(pipe_end[1]);
		dup2(pipe_end[0], 0);
		close(pipe_end[0]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipe_end[0]);
		dup2(pipe_end[1], 1);
		close(pipe_end[1]);
		if (fd == 0)
			exit(1);
		else
			ft_exegguttor(cmd, env);
	}
}

/*La idea de momento, llamar a esta función desde main-shell cuando sepamos
que no hay built in, pasasrle la struct de input y el entorno debería ejecutar
con o sin pipes sin problema*/

int	ft_cmd_driver(t_command *cmds, char **env, t_data *d)
{
	int			curr_cmd;
	pid_t		pid;

	curr_cmd = 0;
	pid = fork();
	if (pid == -1)
		perror("cascaribash: fork process failed");
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
	{
		while (curr_cmd < d->in.cmd_n - 1)
		{
			ft_is_heredoc(&cmds[curr_cmd]);
			ft_pipex(&cmds[curr_cmd++], env, 1);
		}
		ft_is_heredoc(&cmds[curr_cmd]);
		ft_exegguttor(&cmds[curr_cmd], env);
	}
	if (ft_is_biexit(cmds[curr_cmd].cmd_line))
		bi_exit(d, &d->in);
	return (0);
}

/**
 * TODO: redirecciones!-> comprobar si hay in/out file justo antes de
 *			cada llamada a exegguttor, y hacer dup con los fd si es así
 */