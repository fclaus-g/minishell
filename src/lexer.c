/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:39:07 by pgruz11           #+#    #+#             */
/*   Updated: 2023/11/28 16:53:06 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_wordcnt_qt(char *str)
{
    int	cnt = 0;
    int	in_qt = false;
    int	encounteredNonSpace = false;

    if (str == NULL || *str == '\0')
        return 0;

    // Iterate through each character in the string
    for (int i = 0; str[i] != '\0'; ++i) {
        // Check if the current character is a space or a punctuation mark
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == ',' || str[i] == '.' || str[i] == '?' || str[i] == '!' || str[i] == ';') {
            // If we are not inside quotes, consider it as a word separator
            if (!in_qt && encounteredNonSpace) {
                ++cnt;
            }

            // Skip consecutive spaces
            while (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\n' || str[i + 1] == '\r') {
                ++i;
            }
        } else if (str[i] == '"' || str[i] == '\'') {
            // Flip the in_qt flag when encountering a quote
            in_qt = !in_qt;
        } else {
            // Mark that we've encountered a non-space character
            encounteredNonSpace = true;
        }
    }

    // Check if the string consists only of spaces
    if (!encounteredNonSpace && !in_qt) {
        return 0;
    }

    // Increment the word count if the last word is not followed by a space or punctuation
    if (!in_qt && encounteredNonSpace) {
        ++cnt;
    }

    return cnt;
}