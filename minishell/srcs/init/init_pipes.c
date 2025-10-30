/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:04:24 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/28 13:45:07 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_pipes(t_commands *cmds)
{
	int	i;

	i = 0;
	cmds->pipe = (t_pipe *)ft_calloc(cmds->num_cmds, sizeof(t_pipe));
	while (i < cmds->num_cmds)
	{
		cmds->pipe[i].fd = (int *)ft_calloc(sizeof(int), 3);
		if (!cmds->pipe[i].fd)
			exit(6);
		if (pipe(cmds->pipe[i].fd) == -1)
			exit (7);
		i++;
	}
}
