/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:52:00 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:38:44 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_path(t_data *data, t_commands *cmds, int num_cmd)
{
	cmds->cmd[num_cmd].path = get_cmd_path(cmds, num_cmd);
	if (!cmds->cmd[num_cmd].path)
		return (CMD_NOT_FOUND);
	if (execve(cmds->cmd[num_cmd].path, \
		cmds->cmd[num_cmd].args, data->env) == -1)
		error_msg("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
