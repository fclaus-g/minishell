/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:05:42 by pgomez-r          #+#    #+#             */
/*   Updated: 2024/01/19 13:05:58 by pgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_malloc(void **var, size_t size)
{
	*var = malloc(size);
	if (!var)
	{
		printf("cascaribash: malloc error\n");
		return (-1);
	}
	return (0);
}
/*
char *str;
if (ft_malloc((void **)&str, 10 * sizeof(*str)) == -1)
*/
