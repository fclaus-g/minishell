/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:29:49 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/11/30 10:11:53 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *en esta funcion vamos a analizar el input como str y vamos a contar las comillas 
tanto simples como dobles con idea de abstraer todo lo que este entre comillas antes de
hacer split
*!Lo que quiero es contar las comillas y que al recorrer la string, si hay comillas cuente
*!cuanto ocupa, la idea de alguna manera de primeras es que el split guarde ya las comillas para 
*!no trabajar las comillas desde la matriz, me esta costando lo suyo pero ahi estamos 
*/ 
void	ft_lexer(char *str, t_input *input)
{
	int len;
	int c;

	c = -1;
	len = ft_strlen(str);
	while (str[++c] != '\0')
	{
		if (str[c] == '\'')
			ft_check_quotes_str(&str[c], input);
		if (str[c] == '\"')
			ft_check_quotes_str(&str[c], input);
		c++;
	}

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
