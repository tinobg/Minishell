/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:02:41 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/21 18:35:07 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_redirections(t_commands *cmds)
{
	if (!cmds->io)
	{
		cmds->io = malloc(sizeof * cmds->io);
		if (!cmds->io)
			return ;
		cmds->io->in_file = NULL;
		cmds->io->out_file = NULL;
		cmds->io->fd_in = -1;
		cmds->io->fd_out = -1;
		cmds->io->stdin_backup = -1;
		cmds->io->stdout_backup = -1;
		cmds->io->heredoc_eof = NULL;
		cmds->io->error = false;
		cmds->io->cmd_index = -1;
	}
}
