/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:18:47 by brjoves           #+#    #+#             */
/*   Updated: 2024/02/04 18:35:05 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_env(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	if (cmds->cmd[num_cmd].args[1] != NULL)
		return (error_msg("env", NULL, "too many arguments", STDERR));
	if (!data->env)
		return (EXIT_FAILURE);
	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strchr(data->env[i], '='))
			ft_putendl_fd(data->env[i], STDOUT);
		i++;
	}
	return (EXIT_SUCCESS);
}
