/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:18:10 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/29 12:06:37 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_dir_back(char *arg)
{
	char	*aux;
	int		i;
	int		len;
	
	i = (int)ft_strlen(arg) - 1;
	while (arg[i] != '/' && i > 0)
		i--;
	if (i == 0)
	{
		if (chdir("/\0") != 0)
			ft_printf_error("cascaribash: cd error\n");
		return (0);
	}
	aux = malloc(sizeof(char) * (i + 1));
	if (!aux)
		return (ft_printf_error("cacaribash: malloc error \n"), 0);
	len = i;
	aux[i] = '\0';
	i = -1;
	while (++i < len)
		aux[i] = arg[i];
	if (chdir(aux) != 0)
		ft_printf_error("cascaribash: cd error\n");
	free (aux);
	return (0);
}

void	ft_dir_home(t_data *d)
{
	char	*dir;

	dir = ft_getenv(d, "HOME");
	if (dir == NULL)
		ft_printf_error("cascaribash: cd: %s not set\n");
	if (chdir(dir) != 0)
		ft_printf_error("cascaribash: cd error\n");
}

void	bi_cd(t_data *d, t_command *cmd)
{
	char	curr_dir[PATH_MAX];

	getcwd(curr_dir, PATH_MAX);
	if (ft_strdlen(cmd->cmd_tab) == 1 || !ft_strcmp("~", cmd->cmd_tab[1]))
		ft_dir_home(d);
	else if (!ft_strcmp(".", cmd->cmd_tab[1])
		|| !ft_strcmp("./", cmd->cmd_tab[1]))
		return ;
	else if (!ft_strcmp("..", cmd->cmd_tab[1])
		|| !ft_strcmp("../", cmd->cmd_tab[1]))
		ft_dir_back(curr_dir);
	else
	{
		if (chdir(cmd->cmd_tab[1]) != 0)
			ft_printf_error("cascaribash: cd error\n");
	}
	ft_update_pwd(d, curr_dir);
}
/**
 * TODO: check last change-> getcwd at the beginning instead of on ft_dir_back!
 */

void	ft_update_pwd(t_data *d, char *old_pwd)
{
	char	curr_pwd[PATH_MAX];

	getcwd(curr_pwd, PATH_MAX);
	if (!ft_strcmp(old_pwd, curr_pwd))
		return ;
	ft_overwrite_var(d, "OLDPWD", old_pwd);
	ft_overwrite_var(d, "PWD", curr_pwd);
	ft_get_envarray(d);
}

void	bi_pwd(t_data *d)
{
	char	pwd[PATH_MAX];

	(void)d;
	if (getcwd(pwd, PATH_MAX) == NULL)
		ft_printf_error("cascaribash: pwd error\n");
	else
		ft_printf("%s\n", pwd);
}
