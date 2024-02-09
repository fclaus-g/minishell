/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:21:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/02/04 10:56:52 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_fill_elements(t_input *in)
{
	int	i;

	i = -1;
	in->elements = malloc(sizeof(t_element) * in->n_elements);
	if (!in->elements)
		printf("cascaribash: malloc error\n");
	while (++i < in->n_elements)
	{
		in->elements[i].type = '0';
		in->elements[i].data = ft_strdup(in->sp_input[i]);
	}
	in->cmd_n = 0;
	ft_totalfree(in->sp_input);
	in->sp_input = NULL;
}

/*en esta funcion vamos a chequear cada elemento de l array
gestionando en primer lugar si tiene comillas con la funcion
ft_management_quotes, donde comprobaremos si hay dollar y eliminaremos
las comillas necesarias, ACLARACION PARA EL FUTURO, en un array
no necesitamos añadir un puntero mas ya que un ARRAY ES UN PUNTERO
EN SI A LA PRIMERA POSICIÓN DEL ARRAY, si en alguna función vamos a
modificar el valor de un elemento del array si que necesitamos * y &, 
* en el prototipo y & en la llamada a funcion. Si no vamos a modificar
el valor del elemento en si, sino que la función chequeara valores y 
los retornará, se puede pasar en la llamada ft_funcion(*valor).*/
void	ft_check_elements(t_input *in, t_element *array, t_data *d)
{
	int	i;

	(void)d;
	i = -1;
	while (++i < in->n_elements)
	{
		if (ft_quote_in_data(array[i].data))
			ft_management_quotes(&array[i], d);
	}
}

int	ft_its_dollar(char *str)
{
	int	c;

	c = -1;
	while (str[++c])
	{
		if (str[c] == '$')
			return (1);
	}
	return (0);
}

void	ft_dollar_check(t_command *cmd, t_data *d)
{
	int		i;
	char	c;

	i = -1;
	while (++i < cmd->size)
	{
		c = cmd->tokens[i].type;
		if ((c == '0' || c == '\"') && ft_its_dollar(cmd->tokens[i].data))
			ft_expand_dollar(&cmd->tokens[i], d);
	}
}
