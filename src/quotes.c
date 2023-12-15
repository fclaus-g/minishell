/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:22:15 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/12/12 12:18:19 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*funcion que devuelve donde inicia las comillas teniendo en cuenta que puede haber 
caracteres antes de las comillas que deben ser incluidos por ej l"s" -la debe funcionar
con normalidad*/
int ft_start_quotes(char *str)
{
	int c;

	c = -1;
	while (str[++c])
	{
		if (str[c] == '\'' || str[c] == '\"')
		{
			while (str[c] != ' ' && c >= 0)
			{
				c--;
				printf("str[%d]: %c\n", c, str[c]);	
			}
			break;
		}	
	}
	printf("start quotes: %d\n", c);
	return (c);
}

/*vamos a contar las comillas para usarlo como limite para encontrar
el final de la string entre comillas*/
int	ft_count_quotes(char *str)
{
	int c;
	int quotes;

	c = -1;
	quotes = 0;
	while (str[++c])
	{
		if (str[c] == '\'' || str[c] == '\"')
		quotes++;		
	}
	printf("end quotes: %d\n", quotes);
	return (quotes);
}

/*funcion que devuelve la ultima posicion de la string que esta entre comillas
salvando si hay caracteres despues de la ultima comilla sin un espacio en medio*/
int ft_end_quotes(char *str)
{
	int c;
	int quotes;

	c = -1;
	quotes = ft_count_quotes(str);
	while (str[++c])
	{
		if (str[c] == '\'' || str[c] == '\"')
		{
			while (str[c] && quotes >= 0)
			{
				c++;
				if (str[c] == '\'' || str[c] == '\"')
					quotes--;
			}
			break ;
		}
	}
	while (str[c] != ' ' && str[c])
		c++;
	printf("c: %d\n", c);
	return (c);
}

void	ft_check_quotes_str(char *str, t_input *input)
{
	//int	c;
	int quotes;
	int db_quotes;

	//c = -1;
	(void)input;
	quotes = ft_count_char(str, '\'');
	db_quotes = ft_count_char(str, '\"');
	printf("quotes: %d\ndb_quotes: %d\n", quotes, db_quotes);
}

int	ft_count_char(char *str, char c)
{
	int	i;
	int times;

	i = -1;
	times = 0;
	while (str[++i] && str[i])
	{
		if (str[i] == c)
			times++;
	}
	if (times > 1)
		return (times);
	return (0);
}

/*en ft_check_c vamos a ver si elements[i -1] es una derirecccion el tipo c (command) se cambiara por tipo f(file)*/
void	ft_check_c(t_input *input)
{
	int i;

	i = 0;
	while (++i < input->n_elements)
	{
		if (input->element[i].type == 'c' && i > 0)
		{
			if (input->element[i - 1].type == '1' || input->element[i - 1].type == '2' || input->element[i - 1].type == '3' || input->element[i - 1].type == '4')
				input->element[i].type = 'f';
		}
	}
}
void	ft_check_dollar(t_input *input)
{
	int i;

	i = -1;
	while (++i < input->n_elements)
	{
		if (input->element[i].type == 'c' && input->element[i].data[0] == '$')
		{
			input->element[i].type = 'v';
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
/*antiguo ft_checkinput
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
		printf("elemento %s num %d es de tipo %c\n%d fdin\n%d fdout \n priority= %d\n", input->elements[i].data, i, input->elements[i].type, input->elements[i].fd_in, input->elements[i].fd_out, input->elements[i].priority);*/