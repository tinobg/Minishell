/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:53:49 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 14:54:11 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	check_or(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = num_cmd;
	if (g_status_code == 0)
	{
		while (cmds->operators[i - 1] && cmds->operators[i - 1] == OR)
		{
			init_single_cmd(data, cmds, i);
			i++;
		}
		cmds->num_exec = i;
		init_cmd(data, cmds, i);
	}
	else
		init_cmd(data, cmds, num_cmd);
}

static void	check_and(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = num_cmd;
	if (g_status_code != 0)
	{
		while (cmds->operators[i - 1] && cmds->operators[i - 1] == AND)
		{
			init_single_cmd(data, cmds, i);
			i++;
		}
		cmds->num_exec = i;
		init_cmd(data, cmds, i);
	}
	else
		init_cmd(data, cmds, num_cmd);
}

void	check_operators(t_data *data, t_commands *cmds, int num_cmd)
{
	if (cmds->operators[num_cmd - 1] == OR)
		check_or(data, cmds, num_cmd);
	if (cmds->operators[num_cmd - 1] == AND)
		check_and(data, cmds, num_cmd);
}
