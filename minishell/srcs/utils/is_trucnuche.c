/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_trucnuche.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:36:43 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 14:46:42 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

bool	is_in_out_file(t_redirect *io, t_commands *cmds, bool free)
{
	if (!io || (!io->in_file && !io->out_file))
		return (true);
	if (((io->in_file && io->fd_in == -1)
			|| (io->out_file && io->fd_out == -1)) && io->error == true)
	{
		if (free)
		{
			close_fds(cmds, false);
			free_cmds(cmds);
		}
		return (false);
	}
	return (true);
}

bool	is_redirection_cmd(t_commands *cmds, int i)
{
	if (cmds->cmd[i].redirections[0])
		return (true);
	else
		return (false);
}
