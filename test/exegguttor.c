/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exegguttor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:21:34 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/07 17:16:05 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/**
 * @brief Abre los archivos y guardamos su fd nuestras dos variables, prefiero
 * tenerlo en struct que en dos enteros o array de enteros en main
 * Es como estaba en pipex, aquí habrá que modificarla mucho, si es que llega 
 * a servir para algo, la dejo comentada por si acaso
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


/**
 * @brief Función que ejecuta los comandos de la consola con execve, tal
 * como la tenía en pipex 
 * @param cmd entra como una cadena completa, luego se descompone y usa 
 * como haga falta para encontrar rutas y ejecutarla
 * TODO: Modificar para que compruebe y ejecute si es una built =)
 */

void	ft_exegguttor(char *cmd, char **env)
{
	t_command	st;

	get_paths(&st, env);
	split_cmd(&st, cmd);
	if (!ft_is_builtin(st.cmd))
		exit(0);
	if (ft_is_biexit(st.cmd[0]))
		exit(0);
	else
	{
		find_path_index(&st, st.cmd[0]);
		if (execve(st.path_cmd, st.cmd, env) == -1)
		{
			ft_printf_error("cascaribash: command not found: %s\n", st.cmd[0]);
			free_cache(&st, 127);
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
void	ft_pipex(char *cmd, char **env, int fd)
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

/*La idea de momento, llamar a esta función desde main-shell cuando sepamos
que no hay built in, pasasrle la struct de input y el entorno debería ejecutar
con o sin pipes sin problema*/

int	ft_cmd_driver(t_input *in, char **env, t_data *d)
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
		if (in->cmd_n > 1)
		{
			ft_pipex(in->cmd_tab[curr_cmd], env, 0);
			while (curr_cmd < in->cmd_n - 1)
				ft_pipex(in->cmd_tab[curr_cmd++], env, 1);
			ft_exegguttor(in->cmd_tab[curr_cmd], env);
		}
		else
			ft_exegguttor(in->cmd_tab[0], env);
	}
	if (ft_is_biexit(in->cmd_tab[curr_cmd]))
		bi_exit(d, in);
	return (0);
}

/**
 * TODO: adaptar exeguttor a built-in
 */