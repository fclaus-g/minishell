/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exegguttor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:21:34 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/11/21 22:35:52 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/**
 * Abrimos los archivos y guardamos su fd nuestras dos variables, prefiero
 * tenerlo en struct que en dos enteros o array de enteros en main
 *  */

void	ft_openfiles(t_struct *d, char **av, int i)
{
	d->fd_in = open(av[1], O_RDONLY);
	if (d->fd_in == -1)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), av[1]);
		exit(EXIT_FAILURE);
	}
	d->fd_out = open(av[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fd_out == -1)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), av[i]);
		exit(EXIT_FAILURE);
	}
}

void	ft_exegguttor(char *cmd, char **env)
{
	t_command	st;

	get_paths(&st, env);
	split_cmd(&st, cmd);
	find_path_index(&st, st.cmd[0]);
	if (execve(st.path_cmd, st.cmd, env) == -1)
	{
		ft_printf_error("pipex: command not found: %s\n", st.cmd[0]);
		free_cache(&st, 127);
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
void	ft_pipex(char *cmd, char **env, int fd)
{
	pid_t	pid;
	int		pipe_end[2];

	pipe(pipe_end);
	pid = fork();
	if (pid == -1)
		perror("pipex: fork process failed");
	else if (pid > 0)
	{
		close(pipe_end[1]);
		dup2(pipe_end[0], 0);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipe_end[0]);
		dup2(pipe_end[1], 1);
		if (fd == 0)
			exit(1);
		else
			ft_exegguttor(cmd, env);
	}
}

int	ft_exe_inshell(t_input *input, char **av, char **env)
{
	int	curr_cmd;

	if (!env || !*env)
		return (perror("cascaribash: env parse error"), 1);
	// ft_openfiles(&d, av, ac - 1);
	// dup2(d.fd_in, 0);
	// dup2(d.fd_out, 1);
	curr_cmd = 3;
	ft_pipex(av[2], env, d.fd_in);
	while (d.cmd_n < ac - 2)
		ft_pipex(av[d.cmd_n++], env, 1);
	ft_exegguttor(av[ac - 2], env);
	return (0);
}
