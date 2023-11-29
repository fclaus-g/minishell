/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:39:07 by pgruz11           #+#    #+#             */
/*   Updated: 2023/11/29 16:04:35 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_wordcnt_qt(char *str)
{
	int i;
	int	cnt;
	int	in_qt;
	int	non_spc;

	if (str == NULL || *str == '\0')
		return (0);
	non_spc = 0;
	i = -1;
	// Check if there is any character different from spaces or separators
	while (str[++i != '\0'])
	{
		if (str[i] != ' ' || str[i] != '\t' || str[i] != '\n' || str[i] != '\r')
			non_spc = 1;
	}
	// If the string has only spaces or separators, return num of elements 0
	if (!non_spc)
		return (0);
	cnt = 0;
	in_qt = 0;
	i = -1;
	while (str[++i] != '\0') 
	{
		// Check if the current character is a space or separator
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
		{
			// If we are not inside quotes, consider it as a word separator
			if (!in_qt)
				++cnt;
			// Skip consecutive spaces
			while (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\n' || str[i + 1] == '\r')
				++i;
		} 
		else if (str[i] == '"' || str[i] == '\'')
			// Flip the in_qt flag when encountering a quote
			in_qt = !in_qt;
	}
	// Increment the word count if the last word is not followed by a space or punctuation
	if (!in_qt && non_spc)
		++cnt;
	return (cnt);
}
