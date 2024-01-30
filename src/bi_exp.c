/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 23:43:59 by pgruz11           #+#    #+#             */
/*   Updated: 2024/01/30 17:26:04 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_env_update(t_data *d, char *var)
{
	char	**aux;
	int		i;

	aux = malloc(sizeof(char *) * (ft_strdlen(d->env_dup) + 2));
	i = -1;
	while (++i < (int)ft_strdlen(d->env_dup))
		aux[i] = ft_strdup(d->env_dup[i]);
	aux[i] = ft_strdup(var);
	aux[i + 1] = NULL;
	ft_totalfree(d->env_dup);
	return (aux);
}

char	**ft_exp_update(t_data *d, char *var)
{
	char	**aux;
	int		i;

	aux = malloc(sizeof(char *) * (ft_strdlen(d->env_exp) + 2));
	i = -1;
	while (++i < (int)ft_strdlen(d->env_exp))
		aux[i] = ft_strdup(d->env_exp[i]);
	aux[i] = ft_export_varcopy(var);
	aux[i + 1] = NULL;
	ft_totalfree(d->env_exp);
	return (aux);
}

void	bi_export(t_data *d, t_command *cmd)
{
	int	i;

	if (ft_strdlen(cmd->cmd_tab) == 1)
		ft_export_print(d);
	i = 0;
	while (cmd->cmd_tab[++i] != NULL)
	{
		if (ft_valid_identifier(cmd->cmd_tab[i]))
			continue ;
		if (!ft_isvar(cmd->cmd_tab[i]))
		{
			d->env_dup = ft_env_update(d, cmd->cmd_tab[i]);
			ft_get_envarray(d);
			d->env_exp = ft_exp_update(d, cmd->cmd_tab[i]);
			ft_export_order(d->env_exp);
		}
		else
		{
			d->env_exp = ft_exp_update(d, cmd->cmd_tab[i]);
			ft_export_order(d->env_exp);
		}
	}
}

/*EXPORT RULES
Naming: The variable name must begin with a letter (a to z or A to Z) or an
underscore (_), followed by letters, digits (0 to 9), or underscores.
Special characters are not allowed along the whole line.
No spaces around the equals sign; VAR=value is correct, VAR = value is not
No command substitution: The value assigned to the variable should not be the
result of a command substitution.
No special shell characters: (; & | > >> < * ? () $ # {} [] ! \); unless they
are properly escaped or enclose in quotes.*/