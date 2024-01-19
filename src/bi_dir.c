/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:18:10 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/16 23:48:59 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_dir_back(char *arg)
{
	char	*aux;
	int		i;
	int		len;
	
	i = (int)ft_strlen(arg) - 1;
	while (arg[i] != '/' && i > 0)
		i--;
	if (i == 0)
		return ("/\0");
	aux = malloc(sizeof(char) * (i + 1));
	if (!aux)
		return (ft_printf_error("cacaribash: malloc error \n"), NULL);
	len = i;
	aux[i] = '\0';
	i = -1;
	while (++i < len)
		aux[i] = arg[i];
	return (aux);
}

char	*ft_get_dir(char *arg)
{
	char	curr_dir[PATH_MAX];

	if (!ft_strcmp("..", arg) || !ft_strcmp("../", arg))
		return (ft_dir_back(getcwd(curr_dir, PATH_MAX)));
	return (arg);
}

void	bi_cd(t_data *d, t_command *cmd)
{
	char	*dir;

	if (ft_strdlen(cmd->cmd_tab) == 1 || !ft_strcmp("~", cmd->cmd_tab[1]))
	{
		dir = ft_getenv(d, "HOME");
		if (dir == NULL)
			ft_printf_error("cascaribash: cd: %s not set\n");
		if (chdir(dir) != 0)
			ft_printf_error("cascaribash: cd error\n");
	}
	else if (!ft_strcmp(".", cmd->cmd_tab[1])
		|| !ft_strcmp("./", cmd->cmd_tab[1]))
		return ;
	else
	{
		dir = ft_get_dir(cmd->cmd_tab[1]);
		if (chdir(dir) != 0)
			ft_printf_error("cd error\n");
	}
	if (dir != NULL)
		free(dir);
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
