/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:09:57 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/04 16:12:26 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	wait_child(t_commands *cmds)
{
	int	i;
	int	status;
	int	save_status;

	close_pipes_fd(cmds);
	i = -1;
	status = 0;
	save_status = 0;
	while (++i < cmds->num_exec - 1)
		waitpid(cmds->pid[i], NULL, 0);
	waitpid(cmds->pid[i], &save_status, 0);
	if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else
		status = cmds->exit_value;
	return (status);
}

int	execute(t_data *data, t_commands *cmds)
{
	int	status_code;

	status_code = 0;
	while (cmds->num_exec < cmds->num_cmds)
	{
		if (cmds->cmd[cmds->num_exec].args[0] && \
			cmds->operators[cmds->num_exec] \
			!= PIPE && is_builtin_empty(cmds))
			exec_builtin_empty(cmds, data);
		else
		{
			status_code = exec_child(data, cmds, cmds->num_exec);
			g_status_code = wait_child(cmds);
			if (status_code != 0)
				g_status_code = status_code;
			if (cmds->num_exec < cmds->num_cmds)
				check_operators(data, cmds, cmds->num_exec);
		}
	}
	return (g_status_code);
}

int	execute_cmd(t_data *data, t_commands *cmds, int num_cmd)
{
	int	status_code;

	if (cmds->operators[0])
		create_pipes(cmds, num_cmd);
	if (is_redirection_cmd(cmds, num_cmd)
		&& is_in_out_file(cmds->io, cmds, true) == false)
		exit_minishell(data, EXIT_FAILURE);
	redirect_io(cmds->io, num_cmd);
	close_fds(cmds, false);
	if (is_builtin(cmds->cmd[num_cmd].args[0]))
		status_code = exec_builtins(data, cmds, num_cmd);
	else
	{
		if (ft_strchr(cmds->cmd[num_cmd].args[0], '/') == NULL)
		{
			status_code = execute_path(data, cmds, num_cmd);
			if (status_code != CMD_NOT_FOUND)
				free_exit(data, cmds, status_code);
		}
		status_code = execute_local(data, cmds, num_cmd);
	}
	free_cmds(cmds);
	exit_minishell(data, status_code);
	return (status_code);
}
