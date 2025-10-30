/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_local.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:53:53 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/04 15:13:25 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	input_is_dir(char *cmd)
{
	struct stat	buf;

	stat(cmd, &buf);
	return (S_ISDIR(buf.st_mode));
}

static int	valid_cmd_not_found(t_data *data, char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL
		&& get_env_var_index(data->env, "PATH") != -1)
		return (error_msg(cmd, NULL, "command not found", CMD_NOT_FOUND));
	if (access(cmd, F_OK) != 0)
		return (error_msg(cmd, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (input_is_dir(cmd))
		return (error_msg(cmd, NULL, "Is a directory", CMD_NOT_EXEC));
	else if (access(cmd, X_OK) != 0)
		return (error_msg(cmd, NULL, strerror(errno), CMD_NOT_EXEC));
	return (0);
}

int	execute_local(t_data *data, t_commands *cmds, int num_cmd)
{
	int	result;

	result = valid_cmd_not_found(data, cmds->cmd[num_cmd].args[0]);
	if (result != 0)
		return (result);
	if (execve(cmds->cmd[num_cmd].args[0], cmds->cmd[num_cmd].args, \
		data->env) == -1)
		return (error_msg("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}
