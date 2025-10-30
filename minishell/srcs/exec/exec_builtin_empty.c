/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_empty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:39:13 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/04 16:12:20 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_builtin_empty(t_commands *cmds)
{
	if (ft_strncmp(cmds->cmd[0].args[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmds->cmd[0].args[0], "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmds->cmd[0].args[0], "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmds->cmd[0].args[0], "export", 7) == 0 && \
			cmds->cmd[0].args[1])
		return (true);
	else
		return (false);
}

static void	cd_case(t_commands *cmds, t_data *data)
{
	char	*path;

	cmds->pid[0] = fork();
	if (cmds->pid[0] == -1)
		error_msg("fork", NULL, strerror(errno), EXIT_FAILURE);
	else if (cmds->pid[0] == 0)
	{
		if (is_redirection_cmd(cmds, 0)
			&& is_in_out_file(cmds->io, cmds, true) == false)
			exit_minishell(data, EXIT_FAILURE);
		redirect_io(cmds->io, 0);
		close_fds(cmds, false);
		path = get_env_var_value(data->env, PWD);
		if (!path)
			;
		else
			ft_putendl_fd(path, STDOUT);
		free_cmds(cmds);
		exit_minishell(data, 0);
	}
}

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

void	exec_builtin_empty(t_commands *cmds, t_data *data)
{
	if (is_redirection_cmd(cmds, cmds->num_exec))
		handle_redirections(cmds, cmds->num_exec);
	cmds->num_exec++;
	if (is_redirection_cmd(cmds, 0)
		&& is_in_out_file(cmds->io, cmds, false) == false)
		g_status_code = 1;
	else
	{
		g_status_code = exec_builtins(data, cmds, 0);
		if (ft_strncmp(cmds->cmd[0].args[0], "cd", 3) == 0 && \
			cmds->cmd[0].args[1] && g_status_code == 0 && \
			ft_strncmp(cmds->cmd[0].args[1], "-", 2) == 0)
		{
			cd_case(cmds, data);
			g_status_code = wait_child(cmds);
		}
	}
}
