/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:19:11 by brjoves           #+#    #+#             */
/*   Updated: 2024/02/02 17:13:05 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_unset(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;
	int	index;
	int	status_code;

	status_code = EXIT_SUCCESS;
	i = 1;
	while (cmds->cmd[num_cmd].args[i])
	{
		if (is_valid_var_name(cmds->cmd[num_cmd].args[i]) == false)
		{
			status_code = error_msg("unset", cmds->cmd[num_cmd].args[i],
					"not a valid identifier", EXIT_FAILURE);
		}
		else
		{
			index = get_env_var_index(data->env, cmds->cmd[num_cmd].args[i]);
			if (index != -1)
				env_var_remove(data, index);
		}
		i++;
	}
	return (status_code);
}
