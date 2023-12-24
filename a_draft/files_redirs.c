/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:19:48 by pgomez-r          #+#    #+#             */
/*   Updated: 2023/12/23 20:19:17 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Primera idea que tuve para guardar los diferentes files (si hay más de uno)
de entrada y salida en una matriz str para luego poder ir moviendo stdin/stdout
de uno a otro y modificando los archivos si es necesario
Voy a intentar evitar este método para ahorrarnos más reservas/liberaciones de
memoría, pero lo dejo guardado aquí por si acaso necesitamos probarlo*/
void	ft_find_files(t_input *in, t_command *cmds)
{
	int		i;
	int		j;
	char	*in;
	char	*out;

	in = NULL;
	out = NULL;
	i = -1;
	while (++i < in->cmd_n)
	{
		j = -1;
		while (++j < cmds[i].size)
		{
			if (cmds[i].tokens[j].type == 'i')
			{
				in = ft_strjoint(in, cmds[i].tokens[j].data);
				in = ft_addspace(in);
			}
			else if (cmds[i].tokens[j].type == 'o')
			{
				out = ft_strjoint(out, cmds[i].tokens[j].data);
				out = ft_addspace(out);
			}
		}
		if (in != NULL)
			cmds[i].infs = ft_split(in, ' ');
		if (out != NULL)
			cmds[i].outfs = ft_split(out, ' ');
	}
}
/**
 * TODO: acortar > plantearla para un solo cmd y llamarla en bucle 
 */