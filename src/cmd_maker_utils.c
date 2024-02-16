/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_maker_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:19:48 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/02/16 18:23:46 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Función para calcular cuantos elementos de un tipo tenemos en la linea total 
de input. Para que podamos usarla correctamente en cmd_maker, depende de que la
comprobación previa de sintaxis funcione correctamente y "aborte" misión antes 
si hay fallos de ese tipo*/
int	ft_element_cnt(t_input	*in, char c)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = -1;
	while (++i < in->n_elements)
	{
		if (in->elements[i].type == c)
			cnt++;
	}
	return (cnt);
}

int	ft_cmd_size(t_input *in, int *start)
{
	int	i;
	int	size;

	i = *(start);
	size = 0;
	if (in->elements[i].type == '|')
		i++;
	while (i < in->n_elements && in->elements[i].type != '|')
	{
		size++;
		i++;
	}
	*(start) = i;
	return (size);
}

char	*ft_addspace(char *str)
{
	char	*aux;
	int		i;

	aux = malloc(sizeof(char) * ft_strlen(str) + 2);
	i = 0;
	while (str[i] != '\0')
	{
		aux[i] = str[i];
		i++;
	}
	aux[i] = ' ';
	aux[i + 1] = '\0';
	free(str);
	return (aux);
}

void	ft_init_files(t_command *cmd)
{
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->fd_error = -1;
	cmd->paths = NULL;
	cmd->path_cmd = NULL;
	cmd->cmd_tab = NULL;
	cmd->cmd_line = NULL;
}

t_element *ft_delete_element(t_command *cmd, int pos)
{
	int			i;
	int			j;
	t_element	*aux;

	i = 0;
	j = -1;
	aux = malloc(sizeof(t_element) * cmd->size - 1);
	while (++j < cmd->size)
	{
		if (j != pos)
		{
			aux[i].data = ft_strdup(cmd->tokens[j].data);
			aux[i++].type = cmd->tokens[j].type;
		}
	}
	i = -1;
	while (++i < cmd->size)
		ft_free_str(cmd->tokens[i].data);
	free (cmd->tokens);
	cmd->size--;
	return (aux);
}
