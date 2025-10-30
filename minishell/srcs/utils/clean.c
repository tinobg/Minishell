/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:21:47 by brjoves           #+#    #+#             */
/*   Updated: 2024/02/02 16:23:26 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_cmd(t_commands *cmds)
{
	int (i) = 0;
	int (j);
	while (i < cmds->num_exec)
	{
		j = 0;
		while (cmds->cmd[i].args[j] != NULL)
			free(cmds->cmd[i].args[j++]);
		free(cmds->cmd[i].args[j]);
		free(cmds->cmd[i].args);
		j = 0;
		while (cmds->cmd[i].redirections[j] != NULL)
			free(cmds->cmd[i].redirections[j++]);
		free(cmds->cmd[i].redirections[j]);
		free(cmds->cmd[i].redirections);
		free(cmds->cmd[i].path);
		i++;
	}
	free_io(cmds->io);
	free(cmds->cmd);
}

void	free_io(t_redirect *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_eof)
	{
		unlink(io->in_file);
		free_ptr(io->heredoc_eof);
	}
	else if (io->in_file)
		free_ptr(io->in_file);
	else if (io->out_file)
		free_ptr(io->out_file);
	free_ptr(io);
}

void	free_cmds(t_commands *cmds)
{
	int (i) = 0;
	if (cmds->cmds != NULL)
	{
		free_cmd(cmds);
		free_pipes(cmds);
		while (cmds->cmds[i] != NULL)
			free(cmds->cmds[i++]);
		free(cmds->cmds[i]);
		free(cmds->cmds);
		i = 0;
		if (cmds->paths != NULL)
		{
			while (cmds->paths[i] != NULL)
				free(cmds->paths[i++]);
			free(cmds->paths[i]);
		}
		free(cmds->paths);
		free(cmds->operators);
		free(cmds->pid);
	}
	free(cmds);
}

void	close_fds(t_commands *cmds, bool reset_io)
{
	if (cmds->io)
	{
		if (cmds->io->fd_in != -1)
			close(cmds->io->fd_in);
		if (cmds->io->fd_out != -1)
			close(cmds->io->fd_out);
		if (reset_io == true)
			restore_io(cmds->io);
	}
	close_pipes(cmds);
}

void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
