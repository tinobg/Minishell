/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:47:15 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:40:53 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_pipes(t_commands *cmds, int num_cmd)
{
	int	num_pipes;

	num_pipes = 0;
	while (cmds->operators[num_cmd] && cmds->operators[num_cmd] == PIPE)
	{
		num_cmd = num_cmd + 1;
		num_pipes++;
	}
	return (num_pipes + 1);
}

static void	setup_redirections(t_commands *cmds, int num_cmd, t_data *data)
{
	cmds->pid[num_cmd] = fork();
	if (cmds->pid[num_cmd] == -1)
		error_msg("fork", NULL, strerror(errno), EXIT_FAILURE);
	else if (cmds->pid[num_cmd] == 0)
	{
		if (is_redirection_cmd(cmds, num_cmd)
			&& is_in_out_file(cmds->io, cmds, true) == false)
			exit_minishell(data, EXIT_FAILURE);
		redirect_io(cmds->io, num_cmd);
		close_fds(cmds, false);
		free_cmds(cmds);
		exit_minishell(data, 0);
	}
}

int	exec_child(t_data *data, t_commands *cmds, int num_cmd)
{
	cmds->num_exec = cmds->num_exec + count_pipes(cmds, num_cmd);
	while (num_cmd < cmds->num_cmds)
	{
		if (is_redirection_cmd(cmds, num_cmd))
			handle_redirections(cmds, num_cmd);
		if (cmds->cmds[num_cmd] && cmds->cmd[num_cmd].args[0])
		{
			cmds->pid[num_cmd] = fork();
			if (cmds->pid[num_cmd] == -1)
				return (error_msg("fork", NULL, strerror(errno),
						EXIT_FAILURE));
			else if (cmds->pid[num_cmd] == 0)
				execute_cmd(data, cmds, num_cmd);
		}
		if (!cmds->cmd[num_cmd].args[0] && cmds->cmd[num_cmd].redirections[0])
			setup_redirections(cmds, num_cmd, data);
		if (cmds->operators[num_cmd] && cmds->operators[num_cmd] == PIPE)
			num_cmd++;
		else
			num_cmd = cmds->num_cmds;
	}
	return (0);
}
