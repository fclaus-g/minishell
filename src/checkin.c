/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:58:04 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/11/29 11:07:14 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*En esta funcion voy a tratar de chquear la matriz que contiene el input spliteado por espacios
con la intencion de clasificar los elementos en built-in, redirecciones, pipes, etc. y tratar 
de darle un orden de ejecucion a cada uno de ellos. Dentro podria incluir la funcion ft_is_builtin, ft_is_redir
ft_is_pipe lo ideal seria tambien saber diferenciar un comando de un archivo, AUN NO  SE DE QUE MANERA.
Una vez que sepa que tipo de elemento es cada uno, podria ir guardando en la estructura t_element
el tipo de elemento y su contenido en str, para luego poder ejecutarlo en el orden que corresponda.
Y a continuacion comenzar a programar los builtins, detecto a priori que desde aqui no podria a no ser que pase la struct
con el env guardado o que la linkee en la struct general data
IMPORTANTE ESTABLECER LA PRIORIDAD | DIFERENCIAR ENTRE REDIRECCIONES DE ENTRADA Y SALIDA
DIFERENCIAR ENTRE COMANDO Y ARCHIVO
*/
void	ft_checkinput(t_input *input)
{
	int i;

	i = -1;
	while (++i < input->n_elements)
	{
		if (ft_is_builtin(input->elements[i].data, input))
		{
			input->elements[i].type = 'b';
			input->is_built++;
		}
		else if (input->elements[i].data[0] == '-')
		{
			input->elements[i].type = 'f';
			input->is_flag++;
		}
		else if (ft_is_redir(input->elements[i].data))
		{
			input->elements[i].type = ft_is_redir(input->elements[i].data) + 48;//vamos a usar un char numerico para las redirecciones 1= > 2= >> 3= < 4= <<;
			input->is_redir++;
		}
		else if (ft_is_pipe(input->elements[i].data))
		{
			input->elements[i].type = 'p';
			input->n_pipe++;
		}
		else
			input->elements[i].type = 'c';
		printf("elemento %s num %d es de tipo %c\n%d fdin\n%d fdout \n priority= %d\n", input->elements[i].data, i, input->elements[i].type, input->elements[i].fd_in, input->elements[i].fd_out, input->elements[i].priority);
	}
}
/*en ft_check_c vamos a ver si elements[i -1] es una derirecccion el tipo c (command) se cambiara por tipo f(file)*/
void	ft_check_c(t_input *input)
{
	int i;

	i = 0;
	while (++i < input->n_elements)
	{
		if (input->elements[i].type == 'c' && i > 0)
		{
			if (input->elements[i - 1].type == '1' || input->elements[i - 1].type == '2' || input->elements[i - 1].type == '3' || input->elements[i - 1].type == '4')
				input->elements[i].type = 'f';
		}
	}
}

void	ft_check_dollar(t_input *input)
{
	int i;

	i = -1;
	while (++i < input->n_elements)
	{
		if (input->elements[i].type == 'c' && input->elements[i].data[0] == '$')
		{
			input->elements[i].type = 'v';
		}
	}
}

int	ft_is_builtin(char *str, t_input *input)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ft_echo(input), 1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (ft_pwd(input), 1);
	else if (ft_strcmp(str, "export") == 0)
		return (ft_export(input), 1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (ft_env(input), 1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

int	ft_is_redir(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (2);
	else if (ft_strcmp(str, "<") == 0)
		return (3);
	else if (ft_strcmp(str, "<<") == 0)
		return (4);
	else
		return (0);
}

int	ft_is_pipe(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	else
		return (0);
}
