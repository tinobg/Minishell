/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:18:41 by brjoves           #+#    #+#             */
/*   Updated: 2024/02/04 18:36:32 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	n_option(t_commands *cmds, int num_cmd)
{
	if (cmds->cmd[num_cmd].args[1]
		&& ft_strncmp(cmds->cmd[num_cmd].args[1], "-n", 3) == 0)
		return (true);
	return (false);
}

int	builtin_echo(t_commands *cmds, int num_cmd)
{
	int		i;
	bool	n;

	n = n_option(cmds, num_cmd);
	if (n == true)
		i = 2;
	else
		i = 1;
	while (cmds->cmd[num_cmd].args[i])
	{
		ft_putstr_fd(cmds->cmd[num_cmd].args[i], STDOUT_FILENO);
		if (cmds->cmd[num_cmd].args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
