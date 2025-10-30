/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:42:29 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/04 16:12:16 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtins(t_data *data, t_commands *cmds, int num_cmd)
{
	int	cmd_code;

	cmd_code = CMD_NOT_FOUND;
	if (ft_strncmp(cmds->cmd[num_cmd].args[0], "echo", 5) == 0)
		cmd_code = builtin_echo(cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "exit", 5) == 0)
		cmd_code = builtin_exit(data, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "pwd", 4) == 0)
		cmd_code = builtin_pwd();
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "env", 4) == 0)
		cmd_code = builtin_env(data, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "cd", 3) == 0)
		cmd_code = builtin_cd(data, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "unset", 6) == 0)
		cmd_code = builtin_unset(data, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "export", 7) == 0)
		cmd_code = builtin_export(data, cmds, num_cmd);
	else
		exit(EXIT_SUCCESS);
	return (cmd_code);
}
